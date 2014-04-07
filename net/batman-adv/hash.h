/*
 * Copyright (C) 2006-2012 B.A.T.M.A.N. contributors:
 *
 * Simon Wunderlich, Marek Lindner
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 */

#ifndef _NET_BATMAN_ADV_HASH_H_
#define _NET_BATMAN_ADV_HASH_H_

#include <linux/list.h>

typedef int (*hashdata_compare_cb)(const struct hlist_node *, const void *);

typedef uint32_t (*hashdata_choose_cb)(const void *, uint32_t);
typedef void (*hashdata_free_cb)(struct hlist_node *, void *);

struct hashtable_t {
	struct hlist_head *table;   
	spinlock_t *list_locks;     
	uint32_t size;		    
};

struct hashtable_t *hash_new(uint32_t size);

void hash_destroy(struct hashtable_t *hash);

static inline void hash_delete(struct hashtable_t *hash,
			       hashdata_free_cb free_cb, void *arg)
{
	struct hlist_head *head;
	struct hlist_node *node, *node_tmp;
	spinlock_t *list_lock; 
	uint32_t i;

	for (i = 0; i < hash->size; i++) {
		head = &hash->table[i];
		list_lock = &hash->list_locks[i];

		spin_lock_bh(list_lock);
		hlist_for_each_safe(node, node_tmp, head) {
			hlist_del_rcu(node);

			if (free_cb)
				free_cb(node, arg);
		}
		spin_unlock_bh(list_lock);
	}

	hash_destroy(hash);
}


static inline int hash_add(struct hashtable_t *hash,
			   hashdata_compare_cb compare,
			   hashdata_choose_cb choose,
			   const void *data, struct hlist_node *data_node)
{
	uint32_t index;
	int ret = -1;
	struct hlist_head *head;
	struct hlist_node *node;
	spinlock_t *list_lock; 

	if (!hash)
		goto out;

	index = choose(data, hash->size);
	head = &hash->table[index];
	list_lock = &hash->list_locks[index];

	rcu_read_lock();
	__hlist_for_each_rcu(node, head) {
		if (!compare(node, data))
			continue;

		ret = 1;
		goto err_unlock;
	}
	rcu_read_unlock();

	
	spin_lock_bh(list_lock);
	hlist_add_head_rcu(data_node, head);
	spin_unlock_bh(list_lock);

	ret = 0;
	goto out;

err_unlock:
	rcu_read_unlock();
out:
	return ret;
}

static inline void *hash_remove(struct hashtable_t *hash,
				hashdata_compare_cb compare,
				hashdata_choose_cb choose, void *data)
{
	uint32_t index;
	struct hlist_node *node;
	struct hlist_head *head;
	void *data_save = NULL;

	index = choose(data, hash->size);
	head = &hash->table[index];

	spin_lock_bh(&hash->list_locks[index]);
	hlist_for_each(node, head) {
		if (!compare(node, data))
			continue;

		data_save = node;
		hlist_del_rcu(node);
		break;
	}
	spin_unlock_bh(&hash->list_locks[index]);

	return data_save;
}

#endif 
