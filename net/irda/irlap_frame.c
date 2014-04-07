/*********************************************************************
 *
 * Filename:      irlap_frame.c
 * Version:       1.0
 * Description:   Build and transmit IrLAP frames
 * Status:        Stable
 * Author:        Dag Brattli <dagb@cs.uit.no>
 * Created at:    Tue Aug 19 10:27:26 1997
 * Modified at:   Wed Jan  5 08:59:04 2000
 * Modified by:   Dag Brattli <dagb@cs.uit.no>
 *
 *     Copyright (c) 1998-2000 Dag Brattli <dagb@cs.uit.no>,
 *     All Rights Reserved.
 *     Copyright (c) 2000-2003 Jean Tourrilhes <jt@hpl.hp.com>
 *
 *     This program is free software; you can redistribute it and/or
 *     modify it under the terms of the GNU General Public License as
 *     published by the Free Software Foundation; either version 2 of
 *     the License, or (at your option) any later version.
 *
 *     Neither Dag Brattli nor University of Tromsø admit liability nor
 *     provide warranty for any of this software. This material is
 *     provided "AS-IS" and at no charge.
 *
 ********************************************************************/

#include <linux/skbuff.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <linux/netdevice.h>
#include <linux/irda.h>
#include <linux/slab.h>

#include <net/pkt_sched.h>
#include <net/sock.h>

#include <asm/byteorder.h>

#include <net/irda/irda.h>
#include <net/irda/irda_device.h>
#include <net/irda/irlap.h>
#include <net/irda/wrapper.h>
#include <net/irda/timer.h>
#include <net/irda/irlap_frame.h>
#include <net/irda/qos.h>

static void irlap_send_i_frame(struct irlap_cb *self, struct sk_buff *skb,
			       int command);

static inline void irlap_insert_info(struct irlap_cb *self,
				     struct sk_buff *skb)
{
	struct irda_skb_cb *cb = (struct irda_skb_cb *) skb->cb;

	cb->magic = LAP_MAGIC;
	cb->mtt = self->mtt_required;
	cb->next_speed = self->speed;

	
	self->mtt_required = 0;

	cb->xbofs = self->bofs_count;
	cb->next_xbofs = self->next_bofs;
	cb->xbofs_delay = self->xbofs_delay;

	
	self->xbofs_delay = 0;
	
	self->bofs_count = self->next_bofs;
}

void irlap_queue_xmit(struct irlap_cb *self, struct sk_buff *skb)
{
	
	skb->dev = self->netdev;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb_reset_transport_header(skb);
	skb->protocol = htons(ETH_P_IRDA);
	skb->priority = TC_PRIO_BESTEFFORT;

	irlap_insert_info(self, skb);

	if (unlikely(self->mode & IRDA_MODE_MONITOR)) {
		IRDA_DEBUG(3, "%s(): %s is in monitor mode\n", __func__,
			   self->netdev->name);
		dev_kfree_skb(skb);
		return;
	}

	dev_queue_xmit(skb);
}

void irlap_send_snrm_frame(struct irlap_cb *self, struct qos_info *qos)
{
	struct sk_buff *tx_skb;
	struct snrm_frame *frame;
	int ret;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	
	tx_skb = alloc_skb(sizeof(struct snrm_frame) +
			   IRLAP_NEGOCIATION_PARAMS_LEN,
			   GFP_ATOMIC);
	if (!tx_skb)
		return;

	frame = (struct snrm_frame *) skb_put(tx_skb, 2);

	
	if (qos)
		frame->caddr = CMD_FRAME | CBROADCAST;
	else
		frame->caddr = CMD_FRAME | self->caddr;

	
	frame->control = SNRM_CMD | PF_BIT;

	if (qos) {
		skb_put(tx_skb, 9); 
		frame->saddr = cpu_to_le32(self->saddr);
		frame->daddr = cpu_to_le32(self->daddr);

		frame->ncaddr = self->caddr;

		ret = irlap_insert_qos_negotiation_params(self, tx_skb);
		if (ret < 0) {
			dev_kfree_skb(tx_skb);
			return;
		}
	}
	irlap_queue_xmit(self, tx_skb);
}

static void irlap_recv_snrm_cmd(struct irlap_cb *self, struct sk_buff *skb,
				struct irlap_info *info)
{
	struct snrm_frame *frame;

	if (pskb_may_pull(skb,sizeof(struct snrm_frame))) {
		frame = (struct snrm_frame *) skb->data;

		
		info->caddr = frame->ncaddr & 0xFE;

		
		if ((info->caddr == 0x00) || (info->caddr == 0xfe)) {
			IRDA_DEBUG(3, "%s(), invalid connection address!\n",
				   __func__);
			return;
		}

		
		info->daddr = le32_to_cpu(frame->saddr);
		info->saddr = le32_to_cpu(frame->daddr);

		
		if (info->saddr != self->saddr) {
			IRDA_DEBUG(2, "%s(), not addressed to us!\n",
				   __func__);
			return;
		}
		irlap_do_event(self, RECV_SNRM_CMD, skb, info);
	} else {
		
		irlap_do_event(self, RECV_SNRM_CMD, skb, NULL);
	}
}

void irlap_send_ua_response_frame(struct irlap_cb *self, struct qos_info *qos)
{
	struct sk_buff *tx_skb;
	struct ua_frame *frame;
	int ret;

	IRDA_DEBUG(2, "%s() <%ld>\n", __func__, jiffies);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	
	tx_skb = alloc_skb(sizeof(struct ua_frame) +
			   IRLAP_NEGOCIATION_PARAMS_LEN,
			   GFP_ATOMIC);
	if (!tx_skb)
		return;

	frame = (struct ua_frame *) skb_put(tx_skb, 10);

	
	frame->caddr = self->caddr;
	frame->control = UA_RSP | PF_BIT;

	frame->saddr = cpu_to_le32(self->saddr);
	frame->daddr = cpu_to_le32(self->daddr);

	
	if (qos) {
		ret = irlap_insert_qos_negotiation_params(self, tx_skb);
		if (ret < 0) {
			dev_kfree_skb(tx_skb);
			return;
		}
	}

	irlap_queue_xmit(self, tx_skb);
}


void irlap_send_dm_frame( struct irlap_cb *self)
{
	struct sk_buff *tx_skb = NULL;
	struct dm_frame *frame;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	tx_skb = alloc_skb(sizeof(struct dm_frame), GFP_ATOMIC);
	if (!tx_skb)
		return;

	frame = (struct dm_frame *)skb_put(tx_skb, 2);

	if (self->state == LAP_NDM)
		frame->caddr = CBROADCAST;
	else
		frame->caddr = self->caddr;

	frame->control = DM_RSP | PF_BIT;

	irlap_queue_xmit(self, tx_skb);
}

void irlap_send_disc_frame(struct irlap_cb *self)
{
	struct sk_buff *tx_skb = NULL;
	struct disc_frame *frame;

	IRDA_DEBUG(3, "%s()\n", __func__);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	tx_skb = alloc_skb(sizeof(struct disc_frame), GFP_ATOMIC);
	if (!tx_skb)
		return;

	frame = (struct disc_frame *)skb_put(tx_skb, 2);

	frame->caddr = self->caddr | CMD_FRAME;
	frame->control = DISC_CMD | PF_BIT;

	irlap_queue_xmit(self, tx_skb);
}

void irlap_send_discovery_xid_frame(struct irlap_cb *self, int S, __u8 s,
				    __u8 command, discovery_t *discovery)
{
	struct sk_buff *tx_skb = NULL;
	struct xid_frame *frame;
	__u32 bcast = BROADCAST;
	__u8 *info;

	IRDA_DEBUG(4, "%s(), s=%d, S=%d, command=%d\n", __func__,
		   s, S, command);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);
	IRDA_ASSERT(discovery != NULL, return;);

	tx_skb = alloc_skb(sizeof(struct xid_frame) + IRLAP_DISCOVERY_INFO_LEN,
			   GFP_ATOMIC);
	if (!tx_skb)
		return;

	skb_put(tx_skb, 14);
	frame = (struct xid_frame *) tx_skb->data;

	if (command) {
		frame->caddr = CBROADCAST | CMD_FRAME;
		frame->control =  XID_CMD | PF_BIT;
	} else {
		frame->caddr = CBROADCAST;
		frame->control =  XID_RSP | PF_BIT;
	}
	frame->ident = XID_FORMAT;

	frame->saddr = cpu_to_le32(self->saddr);

	if (command)
		frame->daddr = cpu_to_le32(bcast);
	else
		frame->daddr = cpu_to_le32(discovery->data.daddr);

	switch (S) {
	case 1:
		frame->flags = 0x00;
		break;
	case 6:
		frame->flags = 0x01;
		break;
	case 8:
		frame->flags = 0x02;
		break;
	case 16:
		frame->flags = 0x03;
		break;
	default:
		frame->flags = 0x02;
		break;
	}

	frame->slotnr = s;
	frame->version = 0x00;

	if (!command || (frame->slotnr == 0xff)) {
		int len;

		if (discovery->data.hints[0] & HINT_EXTENSION) {
			info = skb_put(tx_skb, 2);
			info[0] = discovery->data.hints[0];
			info[1] = discovery->data.hints[1];
		} else {
			info = skb_put(tx_skb, 1);
			info[0] = discovery->data.hints[0];
		}
		info = skb_put(tx_skb, 1);
		info[0] = discovery->data.charset;

		len = IRDA_MIN(discovery->name_len, skb_tailroom(tx_skb));
		info = skb_put(tx_skb, len);
		memcpy(info, discovery->data.info, len);
	}
	irlap_queue_xmit(self, tx_skb);
}

static void irlap_recv_discovery_xid_rsp(struct irlap_cb *self,
					 struct sk_buff *skb,
					 struct irlap_info *info)
{
	struct xid_frame *xid;
	discovery_t *discovery = NULL;
	__u8 *discovery_info;
	char *text;

	IRDA_DEBUG(4, "%s()\n", __func__);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	if (!pskb_may_pull(skb, sizeof(struct xid_frame))) {
		IRDA_ERROR("%s: frame too short!\n", __func__);
		return;
	}

	xid = (struct xid_frame *) skb->data;

	info->daddr = le32_to_cpu(xid->saddr);
	info->saddr = le32_to_cpu(xid->daddr);

	
	if ((info->saddr != self->saddr) && (info->saddr != BROADCAST)) {
		IRDA_DEBUG(0, "%s(), frame is not addressed to us!\n",
			   __func__);
		return;
	}

	if ((discovery = kzalloc(sizeof(discovery_t), GFP_ATOMIC)) == NULL) {
		IRDA_WARNING("%s: kmalloc failed!\n", __func__);
		return;
	}

	discovery->data.daddr = info->daddr;
	discovery->data.saddr = self->saddr;
	discovery->timestamp = jiffies;

	IRDA_DEBUG(4, "%s(), daddr=%08x\n", __func__,
		   discovery->data.daddr);

	discovery_info = skb_pull(skb, sizeof(struct xid_frame));

	
	discovery->data.hints[0] = discovery_info[0];
	if (discovery_info[0] & HINT_EXTENSION) {
		IRDA_DEBUG(4, "EXTENSION\n");
		discovery->data.hints[1] = discovery_info[1];
		discovery->data.charset = discovery_info[2];
		text = (char *) &discovery_info[3];
	} else {
		discovery->data.hints[1] = 0;
		discovery->data.charset = discovery_info[1];
		text = (char *) &discovery_info[2];
	}
	skb->data[skb->len] = '\0';
	strncpy(discovery->data.info, text, NICKNAME_MAX_LEN);
	discovery->name_len = strlen(discovery->data.info);

	info->discovery = discovery;

	irlap_do_event(self, RECV_DISCOVERY_XID_RSP, skb, info);
}

static void irlap_recv_discovery_xid_cmd(struct irlap_cb *self,
					 struct sk_buff *skb,
					 struct irlap_info *info)
{
	struct xid_frame *xid;
	discovery_t *discovery = NULL;
	__u8 *discovery_info;
	char *text;

	if (!pskb_may_pull(skb, sizeof(struct xid_frame))) {
		IRDA_ERROR("%s: frame too short!\n", __func__);
		return;
	}

	xid = (struct xid_frame *) skb->data;

	info->daddr = le32_to_cpu(xid->saddr);
	info->saddr = le32_to_cpu(xid->daddr);

	
	if ((info->saddr != self->saddr) && (info->saddr != BROADCAST)) {
		IRDA_DEBUG(0, "%s(), frame is not addressed to us!\n",
			   __func__);
		return;
	}

	switch (xid->flags & 0x03) {
	case 0x00:
		info->S = 1;
		break;
	case 0x01:
		info->S = 6;
		break;
	case 0x02:
		info->S = 8;
		break;
	case 0x03:
		info->S = 16;
		break;
	default:
		
		return;
	}
	info->s = xid->slotnr;

	discovery_info = skb_pull(skb, sizeof(struct xid_frame));

	if (info->s == 0xff) {
		
		if((discovery_info == NULL) ||
		   !pskb_may_pull(skb, 3)) {
			IRDA_ERROR("%s: discovery frame too short!\n",
				   __func__);
			return;
		}

		discovery = kmalloc(sizeof(discovery_t), GFP_ATOMIC);
		if (!discovery) {
			IRDA_WARNING("%s: unable to malloc!\n", __func__);
			return;
		}

		discovery->data.daddr = info->daddr;
		discovery->data.saddr = self->saddr;
		discovery->timestamp = jiffies;

		discovery->data.hints[0] = discovery_info[0];
		if (discovery_info[0] & HINT_EXTENSION) {
			discovery->data.hints[1] = discovery_info[1];
			discovery->data.charset = discovery_info[2];
			text = (char *) &discovery_info[3];
		} else {
			discovery->data.hints[1] = 0;
			discovery->data.charset = discovery_info[1];
			text = (char *) &discovery_info[2];
		}
		skb->data[skb->len] = '\0';
		strncpy(discovery->data.info, text, NICKNAME_MAX_LEN);
		discovery->name_len = strlen(discovery->data.info);

		info->discovery = discovery;
	} else
		info->discovery = NULL;

	irlap_do_event(self, RECV_DISCOVERY_XID_CMD, skb, info);
}

void irlap_send_rr_frame(struct irlap_cb *self, int command)
{
	struct sk_buff *tx_skb;
	struct rr_frame *frame;

	tx_skb = alloc_skb(sizeof(struct rr_frame), GFP_ATOMIC);
	if (!tx_skb)
		return;

	frame = (struct rr_frame *)skb_put(tx_skb, 2);

	frame->caddr = self->caddr;
	frame->caddr |= (command) ? CMD_FRAME : 0;

	frame->control = RR | PF_BIT | (self->vr << 5);

	irlap_queue_xmit(self, tx_skb);
}

void irlap_send_rd_frame(struct irlap_cb *self)
{
	struct sk_buff *tx_skb;
	struct rd_frame *frame;

	tx_skb = alloc_skb(sizeof(struct rd_frame), GFP_ATOMIC);
	if (!tx_skb)
		return;

	frame = (struct rd_frame *)skb_put(tx_skb, 2);

	frame->caddr = self->caddr;
	frame->caddr = RD_RSP | PF_BIT;

	irlap_queue_xmit(self, tx_skb);
}

static inline void irlap_recv_rr_frame(struct irlap_cb *self,
				       struct sk_buff *skb,
				       struct irlap_info *info, int command)
{
	info->nr = skb->data[1] >> 5;

	
	if (command)
		irlap_do_event(self, RECV_RR_CMD, skb, info);
	else
		irlap_do_event(self, RECV_RR_RSP, skb, info);
}

static void irlap_recv_rnr_frame(struct irlap_cb *self, struct sk_buff *skb,
				 struct irlap_info *info, int command)
{
	info->nr = skb->data[1] >> 5;

	IRDA_DEBUG(4, "%s(), nr=%d, %ld\n", __func__, info->nr, jiffies);

	if (command)
		irlap_do_event(self, RECV_RNR_CMD, skb, info);
	else
		irlap_do_event(self, RECV_RNR_RSP, skb, info);
}

static void irlap_recv_rej_frame(struct irlap_cb *self, struct sk_buff *skb,
				 struct irlap_info *info, int command)
{
	IRDA_DEBUG(0, "%s()\n", __func__);

	info->nr = skb->data[1] >> 5;

	
	if (command)
		irlap_do_event(self, RECV_REJ_CMD, skb, info);
	else
		irlap_do_event(self, RECV_REJ_RSP, skb, info);
}

static void irlap_recv_srej_frame(struct irlap_cb *self, struct sk_buff *skb,
				  struct irlap_info *info, int command)
{
	IRDA_DEBUG(0, "%s()\n", __func__);

	info->nr = skb->data[1] >> 5;

	
	if (command)
		irlap_do_event(self, RECV_SREJ_CMD, skb, info);
	else
		irlap_do_event(self, RECV_SREJ_RSP, skb, info);
}

static void irlap_recv_disc_frame(struct irlap_cb *self, struct sk_buff *skb,
				  struct irlap_info *info, int command)
{
	IRDA_DEBUG(2, "%s()\n", __func__);

	
	if (command)
		irlap_do_event(self, RECV_DISC_CMD, skb, info);
	else
		irlap_do_event(self, RECV_RD_RSP, skb, info);
}

static inline void irlap_recv_ua_frame(struct irlap_cb *self,
				       struct sk_buff *skb,
				       struct irlap_info *info)
{
	irlap_do_event(self, RECV_UA_RSP, skb, info);
}

void irlap_send_data_primary(struct irlap_cb *self, struct sk_buff *skb)
{
	struct sk_buff *tx_skb;

	if (skb->data[1] == I_FRAME) {

		skb->data[1] = I_FRAME | (self->vs << 1);

		skb_get(skb);
		skb_queue_tail(&self->wx_list, skb);

		
		tx_skb = skb_clone(skb, GFP_ATOMIC);
		if (tx_skb == NULL) {
			return;
		}

		self->vs = (self->vs + 1) % 8;
		self->ack_required = FALSE;
		self->window -= 1;

		irlap_send_i_frame( self, tx_skb, CMD_FRAME);
	} else {
		IRDA_DEBUG(4, "%s(), sending unreliable frame\n", __func__);
		irlap_send_ui_frame(self, skb_get(skb), self->caddr, CMD_FRAME);
		self->window -= 1;
	}
}
void irlap_send_data_primary_poll(struct irlap_cb *self, struct sk_buff *skb)
{
	struct sk_buff *tx_skb;
	int transmission_time;

	
	del_timer(&self->poll_timer);

	
	if (skb->data[1] == I_FRAME) {

		skb->data[1] = I_FRAME | (self->vs << 1);

		skb_get(skb);
		skb_queue_tail(&self->wx_list, skb);

		
		tx_skb = skb_clone(skb, GFP_ATOMIC);
		if (tx_skb == NULL) {
			return;
		}

		tx_skb->data[1] |= PF_BIT;

		self->vs = (self->vs + 1) % 8;
		self->ack_required = FALSE;

		irlap_next_state(self, LAP_NRM_P);
		irlap_send_i_frame(self, tx_skb, CMD_FRAME);
	} else {
		IRDA_DEBUG(4, "%s(), sending unreliable frame\n", __func__);

		if (self->ack_required) {
			irlap_send_ui_frame(self, skb_get(skb), self->caddr, CMD_FRAME);
			irlap_next_state(self, LAP_NRM_P);
			irlap_send_rr_frame(self, CMD_FRAME);
			self->ack_required = FALSE;
		} else {
			skb->data[1] |= PF_BIT;
			irlap_next_state(self, LAP_NRM_P);
			irlap_send_ui_frame(self, skb_get(skb), self->caddr, CMD_FRAME);
		}
	}

	transmission_time = self->final_timeout;

	
	self->window = self->window_size;

#ifdef CONFIG_IRDA_DYNAMIC_WINDOW
	transmission_time -= (self->final_timeout * self->bytes_left
			      / self->line_capacity);
	IRDA_DEBUG(4, "%s() adjusting transmission_time : ft=%d, bl=%d, lc=%d -> tt=%d\n", __func__, self->final_timeout, self->bytes_left, self->line_capacity, transmission_time);

	
	self->bytes_left = self->line_capacity;
#endif 

	irlap_start_final_timer(self, self->final_timeout + transmission_time);

}

void irlap_send_data_secondary_final(struct irlap_cb *self,
				     struct sk_buff *skb)
{
	struct sk_buff *tx_skb = NULL;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);
	IRDA_ASSERT(skb != NULL, return;);

	
	if (skb->data[1] == I_FRAME) {

		skb->data[1] = I_FRAME | (self->vs << 1);

		skb_get(skb);
		skb_queue_tail(&self->wx_list, skb);

		tx_skb = skb_clone(skb, GFP_ATOMIC);
		if (tx_skb == NULL) {
			return;
		}

		tx_skb->data[1] |= PF_BIT;

		self->vs = (self->vs + 1) % 8;
		self->ack_required = FALSE;

		irlap_send_i_frame(self, tx_skb, RSP_FRAME);
	} else {
		if (self->ack_required) {
			irlap_send_ui_frame(self, skb_get(skb), self->caddr, RSP_FRAME);
			irlap_send_rr_frame(self, RSP_FRAME);
			self->ack_required = FALSE;
		} else {
			skb->data[1] |= PF_BIT;
			irlap_send_ui_frame(self, skb_get(skb), self->caddr, RSP_FRAME);
		}
	}

	self->window = self->window_size;
#ifdef CONFIG_IRDA_DYNAMIC_WINDOW
	
	self->bytes_left = self->line_capacity;
#endif 

	irlap_start_wd_timer(self, self->wd_timeout);
}

void irlap_send_data_secondary(struct irlap_cb *self, struct sk_buff *skb)
{
	struct sk_buff *tx_skb = NULL;

	
	if (skb->data[1] == I_FRAME) {

		skb->data[1] = I_FRAME | (self->vs << 1);

		skb_get(skb);
		skb_queue_tail(&self->wx_list, skb);

		tx_skb = skb_clone(skb, GFP_ATOMIC);
		if (tx_skb == NULL) {
			return;
		}

		self->vs = (self->vs + 1) % 8;
		self->ack_required = FALSE;
		self->window -= 1;

		irlap_send_i_frame(self, tx_skb, RSP_FRAME);
	} else {
		irlap_send_ui_frame(self, skb_get(skb), self->caddr, RSP_FRAME);
		self->window -= 1;
	}
}

void irlap_resend_rejected_frames(struct irlap_cb *self, int command)
{
	struct sk_buff *tx_skb;
	struct sk_buff *skb;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	
	skb_queue_walk(&self->wx_list, skb) {
		irlap_wait_min_turn_around(self, &self->qos_tx);

		
		tx_skb = skb_copy(skb, GFP_ATOMIC);
		if (!tx_skb) {
			IRDA_DEBUG(0, "%s(), unable to copy\n", __func__);
			return;
		}

		
		tx_skb->data[1] &= 0x0f;

		if (skb_queue_is_last(&self->wx_list, skb))
			tx_skb->data[1] |= PF_BIT; 
		else
			tx_skb->data[1] &= ~PF_BIT; 

		irlap_send_i_frame(self, tx_skb, command);
	}
#if 0 
	while (!skb_queue_empty(&self->txq)) {

		IRDA_DEBUG(0, "%s(), sending additional frames!\n", __func__);
		if (self->window > 0) {
			skb = skb_dequeue( &self->txq);
			IRDA_ASSERT(skb != NULL, return;);

			if ((self->window > 1) &&
			    !skb_queue_empty(&self->txq)) {
				irlap_send_data_primary(self, skb);
			} else {
				irlap_send_data_primary_poll(self, skb);
			}
			kfree_skb(skb);
		}
	}
#endif
}

void irlap_resend_rejected_frame(struct irlap_cb *self, int command)
{
	struct sk_buff *tx_skb;
	struct sk_buff *skb;

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);

	
	skb = skb_peek(&self->wx_list);
	if (skb != NULL) {
		irlap_wait_min_turn_around(self, &self->qos_tx);

		
		tx_skb = skb_copy(skb, GFP_ATOMIC);
		if (!tx_skb) {
			IRDA_DEBUG(0, "%s(), unable to copy\n", __func__);
			return;
		}

		
		tx_skb->data[1] &= 0x0f;

		
		tx_skb->data[1] |= PF_BIT; 

		irlap_send_i_frame(self, tx_skb, command);
	}
}

void irlap_send_ui_frame(struct irlap_cb *self, struct sk_buff *skb,
			 __u8 caddr, int command)
{
	IRDA_DEBUG(4, "%s()\n", __func__);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);
	IRDA_ASSERT(skb != NULL, return;);

	
	skb->data[0] = caddr | ((command) ? CMD_FRAME : 0);

	irlap_queue_xmit(self, skb);
}

static void irlap_send_i_frame(struct irlap_cb *self, struct sk_buff *skb,
			       int command)
{
	
	skb->data[0] = self->caddr;
	skb->data[0] |= (command) ? CMD_FRAME : 0;

	
	skb->data[1] |= (self->vr << 5);  

	irlap_queue_xmit(self, skb);
}

static inline void irlap_recv_i_frame(struct irlap_cb *self,
				      struct sk_buff *skb,
				      struct irlap_info *info, int command)
{
	info->nr = skb->data[1] >> 5;          
	info->pf = skb->data[1] & PF_BIT;      
	info->ns = (skb->data[1] >> 1) & 0x07; 

	
	if (command)
		irlap_do_event(self, RECV_I_CMD, skb, info);
	else
		irlap_do_event(self, RECV_I_RSP, skb, info);
}

static void irlap_recv_ui_frame(struct irlap_cb *self, struct sk_buff *skb,
				struct irlap_info *info)
{
	IRDA_DEBUG( 4, "%s()\n", __func__);

	info->pf = skb->data[1] & PF_BIT;      

	irlap_do_event(self, RECV_UI_FRAME, skb, info);
}

static void irlap_recv_frmr_frame(struct irlap_cb *self, struct sk_buff *skb,
				  struct irlap_info *info)
{
	__u8 *frame;
	int w, x, y, z;

	IRDA_DEBUG(0, "%s()\n", __func__);

	IRDA_ASSERT(self != NULL, return;);
	IRDA_ASSERT(self->magic == LAP_MAGIC, return;);
	IRDA_ASSERT(skb != NULL, return;);
	IRDA_ASSERT(info != NULL, return;);

	if (!pskb_may_pull(skb, 4)) {
		IRDA_ERROR("%s: frame too short!\n", __func__);
		return;
	}

	frame = skb->data;

	info->nr = frame[2] >> 5;          
	info->pf = frame[2] & PF_BIT;      
	info->ns = (frame[2] >> 1) & 0x07; 

	w = frame[3] & 0x01;
	x = frame[3] & 0x02;
	y = frame[3] & 0x04;
	z = frame[3] & 0x08;

	if (w) {
		IRDA_DEBUG(0, "Rejected control field is undefined or not "
		      "implemented.\n");
	}
	if (x) {
		IRDA_DEBUG(0, "Rejected control field was invalid because it "
		      "contained a non permitted I field.\n");
	}
	if (y) {
		IRDA_DEBUG(0, "Received I field exceeded the maximum negotiated "
		      "for the existing connection or exceeded the maximum "
		      "this station supports if no connection exists.\n");
	}
	if (z) {
		IRDA_DEBUG(0, "Rejected control field control field contained an "
		      "invalid Nr count.\n");
	}
	irlap_do_event(self, RECV_FRMR_RSP, skb, info);
}

void irlap_send_test_frame(struct irlap_cb *self, __u8 caddr, __u32 daddr,
			   struct sk_buff *cmd)
{
	struct sk_buff *tx_skb;
	struct test_frame *frame;
	__u8 *info;

	tx_skb = alloc_skb(cmd->len + sizeof(struct test_frame), GFP_ATOMIC);
	if (!tx_skb)
		return;

	
	if (caddr == CBROADCAST) {
		frame = (struct test_frame *)
			skb_put(tx_skb, sizeof(struct test_frame));

		
		frame->saddr = cpu_to_le32(self->saddr);
		frame->daddr = cpu_to_le32(daddr);
	} else
		frame = (struct test_frame *) skb_put(tx_skb, LAP_ADDR_HEADER + LAP_CTRL_HEADER);

	frame->caddr = caddr;
	frame->control = TEST_RSP | PF_BIT;

	
	info = skb_put(tx_skb, cmd->len);
	memcpy(info, cmd->data, cmd->len);

	
	irlap_wait_min_turn_around(self, &self->qos_tx);
	irlap_queue_xmit(self, tx_skb);
}

static void irlap_recv_test_frame(struct irlap_cb *self, struct sk_buff *skb,
				  struct irlap_info *info, int command)
{
	struct test_frame *frame;

	IRDA_DEBUG(2, "%s()\n", __func__);

	if (!pskb_may_pull(skb, sizeof(*frame))) {
		IRDA_ERROR("%s: frame too short!\n", __func__);
		return;
	}
	frame = (struct test_frame *) skb->data;

	
	if (info->caddr == CBROADCAST) {
		if (skb->len < sizeof(struct test_frame)) {
			IRDA_DEBUG(0, "%s() test frame too short!\n",
				   __func__);
			return;
		}

		
		info->daddr = le32_to_cpu(frame->saddr);
		info->saddr = le32_to_cpu(frame->daddr);

		
		if ((info->saddr != self->saddr) &&
		    (info->saddr != BROADCAST)) {
			return;
		}
	}

	if (command)
		irlap_do_event(self, RECV_TEST_CMD, skb, info);
	else
		irlap_do_event(self, RECV_TEST_RSP, skb, info);
}

int irlap_driver_rcv(struct sk_buff *skb, struct net_device *dev,
		     struct packet_type *ptype, struct net_device *orig_dev)
{
	struct irlap_info info;
	struct irlap_cb *self;
	int command;
	__u8 control;
	int ret = -1;

	if (!net_eq(dev_net(dev), &init_net))
		goto out;

	
	self = (struct irlap_cb *) dev->atalk_ptr;

	
	if (!self || self->magic != LAP_MAGIC)
		goto err;

	if ((skb = skb_share_check(skb, GFP_ATOMIC)) == NULL) {
		IRDA_ERROR("%s: can't clone shared skb!\n", __func__);
		goto err;
	}

	
	if (!pskb_may_pull(skb, 2)) {
		IRDA_ERROR("%s: frame too short!\n", __func__);
		goto err;
	}

	command    = skb->data[0] & CMD_FRAME;
	info.caddr = skb->data[0] & CBROADCAST;

	info.pf      = skb->data[1] &  PF_BIT;
	info.control = skb->data[1] & ~PF_BIT; 

	control = info.control;

	
	if ((info.caddr != self->caddr) && (info.caddr != CBROADCAST)) {
		IRDA_DEBUG(0, "%s(), wrong connection address!\n",
			   __func__);
		goto out;
	}
	if (~control & 0x01) {
		irlap_recv_i_frame(self, skb, &info, command);
		goto out;
	}
	if (~control & 0x02) {
		switch (control & 0x0f) {
		case RR:
			irlap_recv_rr_frame(self, skb, &info, command);
			break;
		case RNR:
			irlap_recv_rnr_frame(self, skb, &info, command);
			break;
		case REJ:
			irlap_recv_rej_frame(self, skb, &info, command);
			break;
		case SREJ:
			irlap_recv_srej_frame(self, skb, &info, command);
			break;
		default:
			IRDA_WARNING("%s: Unknown S-frame %02x received!\n",
				__func__, info.control);
			break;
		}
		goto out;
	}
	switch (control) {
	case XID_RSP:
		irlap_recv_discovery_xid_rsp(self, skb, &info);
		break;
	case XID_CMD:
		irlap_recv_discovery_xid_cmd(self, skb, &info);
		break;
	case SNRM_CMD:
		irlap_recv_snrm_cmd(self, skb, &info);
		break;
	case DM_RSP:
		irlap_do_event(self, RECV_DM_RSP, skb, &info);
		break;
	case DISC_CMD: 
		irlap_recv_disc_frame(self, skb, &info, command);
		break;
	case TEST_CMD:
		irlap_recv_test_frame(self, skb, &info, command);
		break;
	case UA_RSP:
		irlap_recv_ua_frame(self, skb, &info);
		break;
	case FRMR_RSP:
		irlap_recv_frmr_frame(self, skb, &info);
		break;
	case UI_FRAME:
		irlap_recv_ui_frame(self, skb, &info);
		break;
	default:
		IRDA_WARNING("%s: Unknown frame %02x received!\n",
				__func__, info.control);
		break;
	}
out:
	ret = 0;
err:
	
	dev_kfree_skb(skb);
	return ret;
}
