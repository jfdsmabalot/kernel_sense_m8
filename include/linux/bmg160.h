#ifndef __BMG160_H__
#define __BMG160_H__

#if (defined __KERNEL__ || defined __linux__)
#define BMG160_U16 unsigned short       
#define BMG160_S16 signed short
#define BMG160_S32 signed int           
#else
#include <linux/limits.h> 


#if USHRT_MAX == 0xFFFF
		
		#define BMG160_U16 unsigned short
		#define BMG160_S16 signed short
#elif UINT_MAX == 0xFFFF
		
		#define BMG160_U16 unsigned int
		#define BMG160_S16 signed int
#else
		#error BMG160_U16 and BMG160_S16 could not be
		#error defined automatically, please do so manually
#endif

#if INT_MAX == 0x7FFFFFFF
		
		#define BMG160_S32 signed int
#elif LONG_MAX == 0x7FFFFFFF
		
		#define BMG160_S32 signed long int
#else
		#error BMG160_S32 could not be
		#error defined automatically, please do so manually
#endif
#endif


/*******************************************************************
* Copyright (C) 2007 Bosch Sensortec GmbH
*
* bmg160.h
*
* Usage:    This header file which includes all function declaration
*
* Author:       gokul.rajendran@in.bosch.com, yogananth.k@in.bosch.com
********************************************************************/
/*  Disclaimer
*
* Common:
* Bosch Sensortec products are developed for the consumer goods industry.
* They may only be used within the parameters of the respective valid
* product data sheet.  Bosch Sensortec products areprovided with the
* express understanding that there is no warranty of fitness for a
* particular purpose.They are not fit for use in life-sustaining,
* safety or security sensitive systems or any system or device
* that may lead to bodily harm or property damage if the system
* or device malfunctions. In addition,Bosch Sensortec products are
* not fit for use in products which interact with motor vehicle systems.
* The resale and or use of products are at the purchasers own risk and
* his own responsibility. The examination of fitness for the intended use
* is the sole responsibility of the Purchaser.
*
* The purchaser shall indemnify Bosch Sensortec from all third party
* claims, including any claims for incidental, or consequential damages,
* arising from any product use not covered by the parameters of
* the respective valid product data sheet or not approved by
* Bosch Sensortec and reimburse Bosch Sensortec for all costs in
* connection with such claims.
*
* The purchaser must monitor the market for the purchased products,
* particularly with regard to product safety and inform Bosch Sensortec
* without delay of all security relevant incidents.
*
* Engineering Samples are marked with an asterisk (*) or (e).
* Samples may vary from the valid technical specifications of the product
* series. They are therefore not intended or fit for resale to third
* parties or for use in end products. Their sole purpose is internal
* client testing. The testing of an engineering sample may in no way
* replace the testing of a product series. Bosch Sensortec assumes
* no liability for the use of engineering samples.
* By accepting the engineering samples, the Purchaser agrees to indemnify
* Bosch Sensortec from all claims arising from the use of engineering
* samples.
*
* Special:
* This software module (hereinafter called "Software") and any information
* on application-sheets (hereinafter called "Information") is provided
* free of charge for the sole purpose to support your application work.
* The Software and Information is subject to the following
* terms and conditions:
*
* The Software is specifically designed for the exclusive use for
* Bosch Sensortec products by personnel who have special experience
* and training. Do not use this Software if you do not have the
* proper experience or training.
*
* This Software package is provided `` as is `` and without any expressed
* or implied warranties,including without limitation, the implied warranties
* of merchantability and fitness for a particular purpose.
*
* Bosch Sensortec and their representatives and agents deny any liability
* for the functional impairment
* of this Software in terms of fitness, performance and safety.
* Bosch Sensortec and their representatives and agents shall not be liable
* for any direct or indirect damages or injury, except as
* otherwise stipulated in mandatory applicable law.
*
* The Information provided is believed to be accurate and reliable.
* Bosch Sensortec assumes no responsibility for the consequences of use
* of such Information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of Bosch. Specifications mentioned in the Information are
* subject to change without notice.
*
* It is not allowed to deliver the source code of the Software
* to any third party without permission of
* Bosch Sensortec.
*/
#define BMG160_BUS_WR_RETURN_TYPE char

#define BMG160_BUS_WR_PARAM_TYPES unsigned char, unsigned char,\
unsigned char *, unsigned char

#define BMG160_BUS_WR_PARAM_ORDER(device_addr, register_addr,\
register_data, wr_len)

#define BMG160_BUS_WRITE_FUNC(device_addr, register_addr,\
register_data, wr_len) bus_write(device_addr, register_addr,\
register_data, wr_len)
#define BMG160_BUS_RD_RETURN_TYPE char
#define BMG160_BUS_RD_PARAM_TYPES unsigned char, unsigned char,\
unsigned char *, unsigned char
#define BMG160_BUS_RD_PARAM_ORDER device_addr, register_addr,\
register_data
#define BMG160_BUS_READ_FUNC(device_addr, register_addr,\
register_data, rd_len)bus_read(device_addr, register_addr,\
register_data, rd_len)
#define BMG160_BURST_RD_RETURN_TYPE char
#define BMG160_BURST_RD_PARAM_TYPES unsigned char,\
unsigned char, unsigned char *, signed int
#define BMG160_BURST_RD_PARAM_ORDER device_addr, register_addr,\
register_data
#define BMG160_BURST_READ_FUNC(device_addr, register_addr,\
register_data, rd_len)burst_read(device_addr, \
register_addr, register_data, rd_len)
#define BMG160_DELAY_RETURN_TYPE void
#define BMG160_DELAY_PARAM_TYPES BMG160_U16
#define BMG160_DELAY_FUNC(delay_in_msec)\
		delay_func(delay_in_msec)
#define BMG160_RETURN_FUNCTION_TYPE			int

#define	BMG160_I2C_ADDR1				0x68
#define	BMG160_I2C_ADDR					BMG160_I2C_ADDR1
#define	BMG160_I2C_ADDR2				0x69




#define BMG160_CHIP_ID_ADDR						0x00


#define BMG160_RATE_X_LSB_ADDR                   0x02
#define BMG160_RATE_X_MSB_ADDR                   0x03
#define BMG160_RATE_Y_LSB_ADDR                   0x04
#define BMG160_RATE_Y_MSB_ADDR                   0x05
#define BMG160_RATE_Z_LSB_ADDR                   0x06
#define BMG160_RATE_Z_MSB_ADDR                   0x07
#define BMG160_TEMP_ADDR                        0x08

#define BMG160_INT_STATUS0_ADDR                 0x09
#define BMG160_INT_STATUS1_ADDR                 0x0A
#define BMG160_INT_STATUS2_ADDR                 0x0B
#define BMG160_INT_STATUS3_ADDR                 0x0C
#define BMG160_FIFO_STATUS_ADDR                 0x0E

#define BMG160_RANGE_ADDR                  0x0F
#define BMG160_BW_ADDR                     0x10
#define BMG160_MODE_LPM1_ADDR              0x11
#define BMG160_MODE_LPM2_ADDR              0x12
#define BMG160_RATED_HBW_ADDR              0x13
#define BMG160_BGW_SOFTRESET_ADDR          0x14
#define BMG160_INT_ENABLE0_ADDR            0x15
#define BMG160_INT_ENABLE1_ADDR            0x16
#define BMG160_INT_MAP_0_ADDR              0x17
#define BMG160_INT_MAP_1_ADDR              0x18
#define BMG160_INT_MAP_2_ADDR              0x19
#define BMG160_INT_0_ADDR                  0x1A
#define BMG160_INT_1_ADDR                  0x1B
#define BMG160_INT_2_ADDR                  0x1C
#define BMG160_INT_4_ADDR                  0x1E
#define BMG160_RST_LATCH_ADDR              0x21
#define BMG160_HIGH_TH_X_ADDR              0x22
#define BMG160_HIGH_DUR_X_ADDR             0x23
#define BMG160_HIGH_TH_Y_ADDR              0x24
#define BMG160_HIGH_DUR_Y_ADDR             0x25
#define BMG160_HIGH_TH_Z_ADDR              0x26
#define BMG160_HIGH_DUR_Z_ADDR             0x27
#define BMG160_SOC_ADDR                        0x31
#define BMG160_A_FOC_ADDR                      0x32
#define BMG160_TRIM_NVM_CTRL_ADDR          0x33
#define BMG160_BGW_SPI3_WDT_ADDR           0x34


#define BMG160_OFC1_ADDR                   0x36
#define BMG160_OFC2_ADDR                       0x37
#define BMG160_OFC3_ADDR                   0x38
#define BMG160_OFC4_ADDR                   0x39
#define BMG160_TRIM_GP0_ADDR               0x3A
#define BMG160_TRIM_GP1_ADDR               0x3B
#define BMG160_SELF_TEST_ADDR              0x3C

#define BMG160_FIFO_CGF1_ADDR              0x3D
#define BMG160_FIFO_CGF0_ADDR              0x3E

#define BMG160_FIFO_DATA_ADDR              0x3F

#define BMG160_RATE_X_LSB_VALUEX__POS        0

#define BMG160_RATE_X_LSB_VALUEX__LEN        8
#define BMG160_RATE_X_LSB_VALUEX__MSK        0xFF
#define BMG160_RATE_X_LSB_VALUEX__REG        BMG160_RATE_X_LSB_ADDR

#define BMG160_RATE_Y_LSB_VALUEY__POS        0
#define BMG160_RATE_Y_LSB_VALUEY__LEN        8
#define BMG160_RATE_Y_LSB_VALUEY__MSK        0xFF
#define BMG160_RATE_Y_LSB_VALUEY__REG        BMG160_RATE_Y_LSB_ADDR

#define BMG160_RATE_Z_LSB_VALUEZ__POS        0
#define BMG160_RATE_Z_LSB_VALUEZ__LEN        8
#define BMG160_RATE_Z_LSB_VALUEZ__MSK        0xFF
#define BMG160_RATE_Z_LSB_VALUEZ__REG        BMG160_RATE_Z_LSB_ADDR

   
#define BMG160_INT_STATUS0_ANY_INT__POS     2
#define BMG160_INT_STATUS0_ANY_INT__LEN     1
#define BMG160_INT_STATUS0_ANY_INT__MSK     0x04
#define BMG160_INT_STATUS0_ANY_INT__REG     BMG160_INT_STATUS0_ADDR

#define BMG160_INT_STATUS0_HIGH_INT__POS    1
#define BMG160_INT_STATUS0_HIGH_INT__LEN    1
#define BMG160_INT_STATUS0_HIGH_INT__MSK    0x02
#define BMG160_INT_STATUS0_HIGH_INT__REG    BMG160_INT_STATUS0_ADDR

 
#define BMG160_INT_STATUSZERO__POS    1
#define BMG160_INT_STATUSZERO__LEN    2
#define BMG160_INT_STATUSZERO__MSK    0x06
#define BMG160_INT_STATUSZERO__REG    BMG160_INT_STATUS0_ADDR

#define BMG160_INT_STATUS1_DATA_INT__POS           7
#define BMG160_INT_STATUS1_DATA_INT__LEN           1
#define BMG160_INT_STATUS1_DATA_INT__MSK           0x80
#define BMG160_INT_STATUS1_DATA_INT__REG           BMG160_INT_STATUS1_ADDR

 
#define BMG160_INT_STATUS1_AUTO_OFFSET_INT__POS    6
#define BMG160_INT_STATUS1_AUTO_OFFSET_INT__LEN    1
#define BMG160_INT_STATUS1_AUTO_OFFSET_INT__MSK    0x40
#define BMG160_INT_STATUS1_AUTO_OFFSET_INT__REG    BMG160_INT_STATUS1_ADDR

#define BMG160_INT_STATUS1_FAST_OFFSET_INT__POS    5
#define BMG160_INT_STATUS1_FAST_OFFSET_INT__LEN    1
#define BMG160_INT_STATUS1_FAST_OFFSET_INT__MSK    0x20
#define BMG160_INT_STATUS1_FAST_OFFSET_INT__REG    BMG160_INT_STATUS1_ADDR

#define BMG160_INT_STATUS1_FIFO_INT__POS           4
#define BMG160_INT_STATUS1_FIFO_INT__LEN           1
#define BMG160_INT_STATUS1_FIFO_INT__MSK           0x10
#define BMG160_INT_STATUS1_FIFO_INT__REG           BMG160_INT_STATUS1_ADDR

#define BMG160_INT_STATUSONE__POS           4
#define BMG160_INT_STATUSONE__LEN           4
#define BMG160_INT_STATUSONE__MSK           0xF0
#define BMG160_INT_STATUSONE__REG           BMG160_INT_STATUS1_ADDR

#define BMG160_INT_STATUS2_ANY_SIGN_INT__POS     3
#define BMG160_INT_STATUS2_ANY_SIGN_INT__LEN     1
#define BMG160_INT_STATUS2_ANY_SIGN_INT__MSK     0x08
#define BMG160_INT_STATUS2_ANY_SIGN_INT__REG     BMG160_INT_STATUS2_ADDR

#define BMG160_INT_STATUS2_ANY_FIRSTZ_INT__POS   2
#define BMG160_INT_STATUS2_ANY_FIRSTZ_INT__LEN   1
#define BMG160_INT_STATUS2_ANY_FIRSTZ_INT__MSK   0x04
#define BMG160_INT_STATUS2_ANY_FIRSTZ_INT__REG   BMG160_INT_STATUS2_ADDR

#define BMG160_INT_STATUS2_ANY_FIRSTY_INT__POS   1
#define BMG160_INT_STATUS2_ANY_FIRSTY_INT__LEN   1
#define BMG160_INT_STATUS2_ANY_FIRSTY_INT__MSK   0x02
#define BMG160_INT_STATUS2_ANY_FIRSTY_INT__REG   BMG160_INT_STATUS2_ADDR

#define BMG160_INT_STATUS2_ANY_FIRSTX_INT__POS   0
#define BMG160_INT_STATUS2_ANY_FIRSTX_INT__LEN   1
#define BMG160_INT_STATUS2_ANY_FIRSTX_INT__MSK   0x01
#define BMG160_INT_STATUS2_ANY_FIRSTX_INT__REG   BMG160_INT_STATUS2_ADDR

#define BMG160_INT_STATUSTWO__POS   0
#define BMG160_INT_STATUSTWO__LEN   4
#define BMG160_INT_STATUSTWO__MSK   0x0F
#define BMG160_INT_STATUSTWO__REG   BMG160_INT_STATUS2_ADDR

#define BMG160_INT_STATUS3_HIGH_SIGN_INT__POS     3
#define BMG160_INT_STATUS3_HIGH_SIGN_INT__LEN     1
#define BMG160_INT_STATUS3_HIGH_SIGN_INT__MSK     0x08
#define BMG160_INT_STATUS3_HIGH_SIGN_INT__REG     BMG160_INT_STATUS3_ADDR

#define BMG160_INT_STATUS3_HIGH_FIRSTZ_INT__POS   2
#define BMG160_INT_STATUS3_HIGH_FIRSTZ_INT__LEN   1
#define BMG160_INT_STATUS3_HIGH_FIRSTZ_INT__MSK   0x04
#define BMG160_INT_STATUS3_HIGH_FIRSTZ_INT__REG  BMG160_INT_STATUS3_ADDR

#define BMG160_INT_STATUS3_HIGH_FIRSTY_INT__POS   1
#define BMG160_INT_STATUS3_HIGH_FIRSTY_INT__LEN   1
#define BMG160_INT_STATUS3_HIGH_FIRSTY_INT__MSK   0x02
#define BMG160_INT_STATUS3_HIGH_FIRSTY_INT__REG   BMG160_INT_STATUS3_ADDR

#define BMG160_INT_STATUS3_HIGH_FIRSTX_INT__POS   0
#define BMG160_INT_STATUS3_HIGH_FIRSTX_INT__LEN   1
#define BMG160_INT_STATUS3_HIGH_FIRSTX_INT__MSK   0x01
#define BMG160_INT_STATUS3_HIGH_FIRSTX_INT__REG   BMG160_INT_STATUS3_ADDR

#define BMG160_INT_STATUSTHREE__POS   0
#define BMG160_INT_STATUSTHREE__LEN   4
#define BMG160_INT_STATUSTHREE__MSK   0x0F
#define BMG160_INT_STATUSTHREE__REG   BMG160_INT_STATUS3_ADDR

#define BMG160_FIFO_STATUS_OVERRUN__POS         7
#define BMG160_FIFO_STATUS_OVERRUN__LEN         1
#define BMG160_FIFO_STATUS_OVERRUN__MSK         0x80
#define BMG160_FIFO_STATUS_OVERRUN__REG         BMG160_FIFO_STATUS_ADDR

#define BMG160_FIFO_STATUS_FRAME_COUNTER__POS   0
#define BMG160_FIFO_STATUS_FRAME_COUNTER__LEN   7
#define BMG160_FIFO_STATUS_FRAME_COUNTER__MSK   0x7F
#define BMG160_FIFO_STATUS_FRAME_COUNTER__REG   BMG160_FIFO_STATUS_ADDR

#define BMG160_RANGE_ADDR_RANGE__POS           0
#define BMG160_RANGE_ADDR_RANGE__LEN           3
#define BMG160_RANGE_ADDR_RANGE__MSK           0x07
#define BMG160_RANGE_ADDR_RANGE__REG           BMG160_RANGE_ADDR

#define BMG160_BW_ADDR_HIGH_RES__POS       7
#define BMG160_BW_ADDR_HIGH_RES__LEN       1
#define BMG160_BW_ADDR_HIGH_RES__MSK       0x80
#define BMG160_BW_ADDR_HIGH_RES__REG       BMG160_BW_ADDR

#define BMG160_BW_ADDR__POS             0
#define BMG160_BW_ADDR__LEN             3
#define BMG160_BW_ADDR__MSK             0x07
#define BMG160_BW_ADDR__REG             BMG160_BW_ADDR

#define BMG160_BW_ADDR_IMG_STB__POS             6
#define BMG160_BW_ADDR_IMG_STB__LEN             1
#define BMG160_BW_ADDR_IMG_STB__MSK             0x40
#define BMG160_BW_ADDR_IMG_STB__REG             BMG160_BW_ADDR

#define BMG160_MODE_LPM1__POS             5
#define BMG160_MODE_LPM1__LEN             3
#define BMG160_MODE_LPM1__MSK             0xA0
#define BMG160_MODE_LPM1__REG             BMG160_MODE_LPM1_ADDR

#define BMG160_MODELPM1_ADDR_SLEEPDUR__POS              1
#define BMG160_MODELPM1_ADDR_SLEEPDUR__LEN              3
#define BMG160_MODELPM1_ADDR_SLEEPDUR__MSK              0x0E
#define BMG160_MODELPM1_ADDR_SLEEPDUR__REG              BMG160_MODE_LPM1_ADDR

#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__POS         7
#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__LEN         1
#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__MSK         0x80
#define BMG160_MODE_LPM2_ADDR_FAST_POWERUP__REG         BMG160_MODE_LPM2_ADDR

#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__POS      6
#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__LEN      1
#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__MSK      0x40
#define BMG160_MODE_LPM2_ADDR_ADV_POWERSAVING__REG      BMG160_MODE_LPM2_ADDR

#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SEL__POS          4
#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SEL__LEN          2
#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SEL__MSK          0x30
#define BMG160_MODE_LPM2_ADDR_EXT_TRI_SEL__REG          BMG160_MODE_LPM2_ADDR

#define BMG160_MODE_LPM2_ADDR_AUTOSLEEPDUR__POS  0
#define BMG160_MODE_LPM2_ADDR_AUTOSLEEPDUR__LEN  3
#define BMG160_MODE_LPM2_ADDR_AUTOSLEEPDUR__MSK  0x07
#define BMG160_MODE_LPM2_ADDR_AUTOSLEEPDUR__REG  BMG160_MODE_LPM2_ADDR

#define BMG160_RATED_HBW_ADDR_DATA_HIGHBW__POS         7
#define BMG160_RATED_HBW_ADDR_DATA_HIGHBW__LEN         1
#define BMG160_RATED_HBW_ADDR_DATA_HIGHBW__MSK         0x80
#define BMG160_RATED_HBW_ADDR_DATA_HIGHBW__REG         BMG160_RATED_HBW_ADDR

#define BMG160_RATED_HBW_ADDR_SHADOW_DIS__POS          6
#define BMG160_RATED_HBW_ADDR_SHADOW_DIS__LEN          1
#define BMG160_RATED_HBW_ADDR_SHADOW_DIS__MSK          0x40
#define BMG160_RATED_HBW_ADDR_SHADOW_DIS__REG          BMG160_RATED_HBW_ADDR

#define BMG160_INT_ENABLE0_DATAEN__POS               7
#define BMG160_INT_ENABLE0_DATAEN__LEN               1
#define BMG160_INT_ENABLE0_DATAEN__MSK               0x80
#define BMG160_INT_ENABLE0_DATAEN__REG               BMG160_INT_ENABLE0_ADDR

#define BMG160_INT_ENABLE0_FIFOEN__POS               6
#define BMG160_INT_ENABLE0_FIFOEN__LEN               1
#define BMG160_INT_ENABLE0_FIFOEN__MSK               0x40
#define BMG160_INT_ENABLE0_FIFOEN__REG               BMG160_INT_ENABLE0_ADDR

#define BMG160_INT_ENABLE0_AUTO_OFFSETEN__POS        2
#define BMG160_INT_ENABLE0_AUTO_OFFSETEN__LEN        1
#define BMG160_INT_ENABLE0_AUTO_OFFSETEN__MSK        0x04
#define BMG160_INT_ENABLE0_AUTO_OFFSETEN__REG        BMG160_INT_ENABLE0_ADDR

#define BMG160_INT_ENABLE1_IT2_OD__POS               3
#define BMG160_INT_ENABLE1_IT2_OD__LEN               1
#define BMG160_INT_ENABLE1_IT2_OD__MSK               0x08
#define BMG160_INT_ENABLE1_IT2_OD__REG               BMG160_INT_ENABLE1_ADDR

#define BMG160_INT_ENABLE1_IT2_LVL__POS              2
#define BMG160_INT_ENABLE1_IT2_LVL__LEN              1
#define BMG160_INT_ENABLE1_IT2_LVL__MSK              0x04
#define BMG160_INT_ENABLE1_IT2_LVL__REG              BMG160_INT_ENABLE1_ADDR

#define BMG160_INT_ENABLE1_IT1_OD__POS               1
#define BMG160_INT_ENABLE1_IT1_OD__LEN               1
#define BMG160_INT_ENABLE1_IT1_OD__MSK               0x02
#define BMG160_INT_ENABLE1_IT1_OD__REG               BMG160_INT_ENABLE1_ADDR

#define BMG160_INT_ENABLE1_IT1_LVL__POS              0
#define BMG160_INT_ENABLE1_IT1_LVL__LEN              1
#define BMG160_INT_ENABLE1_IT1_LVL__MSK              0x01
#define BMG160_INT_ENABLE1_IT1_LVL__REG              BMG160_INT_ENABLE1_ADDR

#define BMG160_INT_MAP_0_INT1_HIGH__POS            3
#define BMG160_INT_MAP_0_INT1_HIGH__LEN            1
#define BMG160_INT_MAP_0_INT1_HIGH__MSK            0x08
#define BMG160_INT_MAP_0_INT1_HIGH__REG            BMG160_INT_MAP_0_ADDR

#define BMG160_INT_MAP_0_INT1_ANY__POS             1
#define BMG160_INT_MAP_0_INT1_ANY__LEN             1
#define BMG160_INT_MAP_0_INT1_ANY__MSK             0x02
#define BMG160_INT_MAP_0_INT1_ANY__REG             BMG160_INT_MAP_0_ADDR

#define BMG160_MAP_1_INT2_DATA__POS                  7
#define BMG160_MAP_1_INT2_DATA__LEN                  1
#define BMG160_MAP_1_INT2_DATA__MSK                  0x80
#define BMG160_MAP_1_INT2_DATA__REG                  BMG160_INT_MAP_1_ADDR

#define BMG160_MAP_1_INT2_FAST_OFFSET__POS           6
#define BMG160_MAP_1_INT2_FAST_OFFSET__LEN           1
#define BMG160_MAP_1_INT2_FAST_OFFSET__MSK           0x40
#define BMG160_MAP_1_INT2_FAST_OFFSET__REG           BMG160_INT_MAP_1_ADDR

#define BMG160_MAP_1_INT2_FIFO__POS                  5
#define BMG160_MAP_1_INT2_FIFO__LEN                  1
#define BMG160_MAP_1_INT2_FIFO__MSK                  0x20
#define BMG160_MAP_1_INT2_FIFO__REG                  BMG160_INT_MAP_1_ADDR

#define BMG160_MAP_1_INT2_AUTO_OFFSET__POS           4
#define BMG160_MAP_1_INT2_AUTO_OFFSET__LEN           1
#define BMG160_MAP_1_INT2_AUTO_OFFSET__MSK           0x10
#define BMG160_MAP_1_INT2_AUTO_OFFSET__REG           BMG160_INT_MAP_1_ADDR

#define BMG160_MAP_1_INT1_AUTO_OFFSET__POS           3
#define BMG160_MAP_1_INT1_AUTO_OFFSET__LEN           1
#define BMG160_MAP_1_INT1_AUTO_OFFSET__MSK           0x08
#define BMG160_MAP_1_INT1_AUTO_OFFSET__REG           BMG160_INT_MAP_1_ADDR

#define BMG160_MAP_1_INT1_FIFO__POS                  2
#define BMG160_MAP_1_INT1_FIFO__LEN                  1
#define BMG160_MAP_1_INT1_FIFO__MSK                  0x04
#define BMG160_MAP_1_INT1_FIFO__REG                  BMG160_INT_MAP_1_ADDR

#define BMG160_MAP_1_INT1_FAST_OFFSET__POS           1
#define BMG160_MAP_1_INT1_FAST_OFFSET__LEN           1
#define BMG160_MAP_1_INT1_FAST_OFFSET__MSK           0x02
#define BMG160_MAP_1_INT1_FAST_OFFSET__REG           BMG160_INT_MAP_1_ADDR

#define BMG160_MAP_1_INT1_DATA__POS                  0
#define BMG160_MAP_1_INT1_DATA__LEN                  1
#define BMG160_MAP_1_INT1_DATA__MSK                  0x01
#define BMG160_MAP_1_INT1_DATA__REG                  BMG160_INT_MAP_1_ADDR

#define BMG160_INT_MAP_2_INT2_HIGH__POS            3
#define BMG160_INT_MAP_2_INT2_HIGH__LEN            1
#define BMG160_INT_MAP_2_INT2_HIGH__MSK            0x08
#define BMG160_INT_MAP_2_INT2_HIGH__REG            BMG160_INT_MAP_2_ADDR

#define BMG160_INT_MAP_2_INT2_ANY__POS             1
#define BMG160_INT_MAP_2_INT2_ANY__LEN             1
#define BMG160_INT_MAP_2_INT2_ANY__MSK             0x02
#define BMG160_INT_MAP_2_INT2_ANY__REG             BMG160_INT_MAP_2_ADDR

#define BMG160_INT_0_ADDR_SLOW_OFFSET_UNFILT__POS          5
#define BMG160_INT_0_ADDR_SLOW_OFFSET_UNFILT__LEN          1
#define BMG160_INT_0_ADDR_SLOW_OFFSET_UNFILT__MSK          0x20
#define BMG160_INT_0_ADDR_SLOW_OFFSET_UNFILT__REG          BMG160_INT_0_ADDR

#define BMG160_INT_0_ADDR_HIGH_UNFILT_DATA__POS            3
#define BMG160_INT_0_ADDR_HIGH_UNFILT_DATA__LEN            1
#define BMG160_INT_0_ADDR_HIGH_UNFILT_DATA__MSK            0x08
#define BMG160_INT_0_ADDR_HIGH_UNFILT_DATA__REG            BMG160_INT_0_ADDR

#define BMG160_INT_0_ADDR_ANY_UNFILT_DATA__POS             1
#define BMG160_INT_0_ADDR_ANY_UNFILT_DATA__LEN             1
#define BMG160_INT_0_ADDR_ANY_UNFILT_DATA__MSK             0x02
#define BMG160_INT_0_ADDR_ANY_UNFILT_DATA__REG             BMG160_INT_0_ADDR

#define BMG160_INT_1_ADDR_FAST_OFFSET_UNFILT__POS            7
#define BMG160_INT_1_ADDR_FAST_OFFSET_UNFILT__LEN            1
#define BMG160_INT_1_ADDR_FAST_OFFSET_UNFILT__MSK            0x80
#define BMG160_INT_1_ADDR_FAST_OFFSET_UNFILT__REG            BMG160_INT_1_ADDR

#define BMG160_INT_1_ADDR_ANY_TH__POS                       0
#define BMG160_INT_1_ADDR_ANY_TH__LEN                       7
#define BMG160_INT_1_ADDR_ANY_TH__MSK                       0x7F
#define BMG160_INT_1_ADDR_ANY_TH__REG                       BMG160_INT_1_ADDR

#define BMG160_INT_2_ADDR_AWAKE_DUR__POS          6
#define BMG160_INT_2_ADDR_AWAKE_DUR__LEN          2
#define BMG160_INT_2_ADDR_AWAKE_DUR__MSK          0xC0
#define BMG160_INT_2_ADDR_AWAKE_DUR__REG          BMG160_INT_2_ADDR

#define BMG160_INT_2_ADDR_ANY_DURSAMPLE__POS      4
#define BMG160_INT_2_ADDR_ANY_DURSAMPLE__LEN      2
#define BMG160_INT_2_ADDR_ANY_DURSAMPLE__MSK      0x30
#define BMG160_INT_2_ADDR_ANY_DURSAMPLE__REG      BMG160_INT_2_ADDR

#define BMG160_INT_2_ADDR_ANY_EN_Z__POS           2
#define BMG160_INT_2_ADDR_ANY_EN_Z__LEN           1
#define BMG160_INT_2_ADDR_ANY_EN_Z__MSK           0x04
#define BMG160_INT_2_ADDR_ANY_EN_Z__REG           BMG160_INT_2_ADDR

#define BMG160_INT_2_ADDR_ANY_EN_Y__POS           1
#define BMG160_INT_2_ADDR_ANY_EN_Y__LEN           1
#define BMG160_INT_2_ADDR_ANY_EN_Y__MSK           0x02
#define BMG160_INT_2_ADDR_ANY_EN_Y__REG           BMG160_INT_2_ADDR

#define BMG160_INT_2_ADDR_ANY_EN_X__POS           0
#define BMG160_INT_2_ADDR_ANY_EN_X__LEN           1
#define BMG160_INT_2_ADDR_ANY_EN_X__MSK           0x01
#define BMG160_INT_2_ADDR_ANY_EN_X__REG           BMG160_INT_2_ADDR

#define BMG160_INT_4_FIFO_WM_EN__POS           7
#define BMG160_INT_4_FIFO_WM_EN__LEN           1
#define BMG160_INT_4_FIFO_WM_EN__MSK           0x80
#define BMG160_INT_4_FIFO_WM_EN__REG           BMG160_INT_4_ADDR

#define BMG160_RST_LATCH_ADDR_RESET_INT__POS           7
#define BMG160_RST_LATCH_ADDR_RESET_INT__LEN           1
#define BMG160_RST_LATCH_ADDR_RESET_INT__MSK           0x80
#define BMG160_RST_LATCH_ADDR_RESET_INT__REG           BMG160_RST_LATCH_ADDR

#define BMG160_RST_LATCH_ADDR_OFFSET_RESET__POS        6
#define BMG160_RST_LATCH_ADDR_OFFSET_RESET__LEN        1
#define BMG160_RST_LATCH_ADDR_OFFSET_RESET__MSK        0x40
#define BMG160_RST_LATCH_ADDR_OFFSET_RESET__REG        BMG160_RST_LATCH_ADDR

#define BMG160_RST_LATCH_ADDR_LATCH_STATUS__POS        4
#define BMG160_RST_LATCH_ADDR_LATCH_STATUS__LEN        1
#define BMG160_RST_LATCH_ADDR_LATCH_STATUS__MSK        0x10
#define BMG160_RST_LATCH_ADDR_LATCH_STATUS__REG        BMG160_RST_LATCH_ADDR

#define BMG160_RST_LATCH_ADDR_LATCH_INT__POS           0
#define BMG160_RST_LATCH_ADDR_LATCH_INT__LEN           4
#define BMG160_RST_LATCH_ADDR_LATCH_INT__MSK           0x0F
#define BMG160_RST_LATCH_ADDR_LATCH_INT__REG           BMG160_RST_LATCH_ADDR

#define BMG160_HIGH_HY_X__POS        6
#define BMG160_HIGH_HY_X__LEN        2
#define BMG160_HIGH_HY_X__MSK        0xC0
#define BMG160_HIGH_HY_X__REG        BMG160_HIGH_TH_X_ADDR

#define BMG160_HIGH_TH_X__POS        1
#define BMG160_HIGH_TH_X__LEN        5
#define BMG160_HIGH_TH_X__MSK        0x3E
#define BMG160_HIGH_TH_X__REG        BMG160_HIGH_TH_X_ADDR

#define BMG160_HIGH_EN_X__POS        0
#define BMG160_HIGH_EN_X__LEN        1
#define BMG160_HIGH_EN_X__MSK        0x01
#define BMG160_HIGH_EN_X__REG        BMG160_HIGH_TH_X_ADDR

#define BMG160_HIGH_HY_Y__POS        6
#define BMG160_HIGH_HY_Y__LEN        2
#define BMG160_HIGH_HY_Y__MSK        0xC0
#define BMG160_HIGH_HY_Y__REG        BMG160_HIGH_TH_Y_ADDR

#define BMG160_HIGH_TH_Y__POS        1
#define BMG160_HIGH_TH_Y__LEN        5
#define BMG160_HIGH_TH_Y__MSK        0x3E
#define BMG160_HIGH_TH_Y__REG        BMG160_HIGH_TH_Y_ADDR

#define BMG160_HIGH_EN_Y__POS        0
#define BMG160_HIGH_EN_Y__LEN        1
#define BMG160_HIGH_EN_Y__MSK        0x01
#define BMG160_HIGH_EN_Y__REG        BMG160_HIGH_TH_Y_ADDR

#define BMG160_HIGH_HY_Z__POS        6
#define BMG160_HIGH_HY_Z__LEN        2
#define BMG160_HIGH_HY_Z__MSK        0xC0
#define BMG160_HIGH_HY_Z__REG        BMG160_HIGH_TH_Z_ADDR

#define BMG160_HIGH_TH_Z__POS        1
#define BMG160_HIGH_TH_Z__LEN        5
#define BMG160_HIGH_TH_Z__MSK        0x3E
#define BMG160_HIGH_TH_Z__REG        BMG160_HIGH_TH_Z_ADDR

#define BMG160_HIGH_EN_Z__POS        0
#define BMG160_HIGH_EN_Z__LEN        1
#define BMG160_HIGH_EN_Z__MSK        0x01
#define BMG160_HIGH_EN_Z__REG        BMG160_HIGH_TH_Z_ADDR

#define BMG160_SLOW_OFFSET_TH__POS          6
#define BMG160_SLOW_OFFSET_TH__LEN          2
#define BMG160_SLOW_OFFSET_TH__MSK          0xC0
#define BMG160_SLOW_OFFSET_TH__REG          BMG160_SOC_ADDR

#define BMG160_SLOW_OFFSET_DUR__POS         3
#define BMG160_SLOW_OFFSET_DUR__LEN         3
#define BMG160_SLOW_OFFSET_DUR__MSK         0x38
#define BMG160_SLOW_OFFSET_DUR__REG         BMG160_SOC_ADDR

#define BMG160_SLOW_OFFSET_EN_Z__POS        2
#define BMG160_SLOW_OFFSET_EN_Z__LEN        1
#define BMG160_SLOW_OFFSET_EN_Z__MSK        0x04
#define BMG160_SLOW_OFFSET_EN_Z__REG        BMG160_SOC_ADDR

#define BMG160_SLOW_OFFSET_EN_Y__POS        1
#define BMG160_SLOW_OFFSET_EN_Y__LEN        1
#define BMG160_SLOW_OFFSET_EN_Y__MSK        0x02
#define BMG160_SLOW_OFFSET_EN_Y__REG        BMG160_SOC_ADDR

#define BMG160_SLOW_OFFSET_EN_X__POS        0
#define BMG160_SLOW_OFFSET_EN_X__LEN        1
#define BMG160_SLOW_OFFSET_EN_X__MSK        0x01
#define BMG160_SLOW_OFFSET_EN_X__REG        BMG160_SOC_ADDR

#define BMG160_AUTO_OFFSET_WL__POS        6
#define BMG160_AUTO_OFFSET_WL__LEN        2
#define BMG160_AUTO_OFFSET_WL__MSK        0xC0
#define BMG160_AUTO_OFFSET_WL__REG        BMG160_A_FOC_ADDR

#define BMG160_FAST_OFFSET_WL__POS        4
#define BMG160_FAST_OFFSET_WL__LEN        2
#define BMG160_FAST_OFFSET_WL__MSK        0x30
#define BMG160_FAST_OFFSET_WL__REG        BMG160_A_FOC_ADDR

#define BMG160_FAST_OFFSET_EN__POS        3
#define BMG160_FAST_OFFSET_EN__LEN        1
#define BMG160_FAST_OFFSET_EN__MSK        0x08
#define BMG160_FAST_OFFSET_EN__REG        BMG160_A_FOC_ADDR

#define BMG160_FAST_OFFSET_EN_Z__POS      2
#define BMG160_FAST_OFFSET_EN_Z__LEN      1
#define BMG160_FAST_OFFSET_EN_Z__MSK      0x04
#define BMG160_FAST_OFFSET_EN_Z__REG      BMG160_A_FOC_ADDR

#define BMG160_FAST_OFFSET_EN_Y__POS      1
#define BMG160_FAST_OFFSET_EN_Y__LEN      1
#define BMG160_FAST_OFFSET_EN_Y__MSK      0x02
#define BMG160_FAST_OFFSET_EN_Y__REG      BMG160_A_FOC_ADDR

#define BMG160_FAST_OFFSET_EN_X__POS      0
#define BMG160_FAST_OFFSET_EN_X__LEN      1
#define BMG160_FAST_OFFSET_EN_X__MSK      0x01
#define BMG160_FAST_OFFSET_EN_X__REG      BMG160_A_FOC_ADDR

#define BMG160_FAST_OFFSET_EN_XYZ__POS      0
#define BMG160_FAST_OFFSET_EN_XYZ__LEN      3
#define BMG160_FAST_OFFSET_EN_XYZ__MSK      0x07
#define BMG160_FAST_OFFSET_EN_XYZ__REG      BMG160_A_FOC_ADDR

#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__POS        4
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__LEN        4
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__MSK        0xF0
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_REMAIN__REG        \
BMG160_TRIM_NVM_CTRL_ADDR

#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__POS          3
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__LEN          1
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__MSK          0x08
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_LOAD__REG          \
BMG160_TRIM_NVM_CTRL_ADDR

#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__POS           2
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__LEN           1
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__MSK           0x04
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_RDY__REG           \
BMG160_TRIM_NVM_CTRL_ADDR

 
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__POS     1
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__LEN     1
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__MSK     0x02
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_TRIG__REG     \
BMG160_TRIM_NVM_CTRL_ADDR

#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__POS     0
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__LEN     1
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__MSK     0x01
#define BMG160_TRIM_NVM_CTRL_ADDR_NVM_PROG_MODE__REG     \
BMG160_TRIM_NVM_CTRL_ADDR

 
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_EN__POS      2
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_EN__LEN      1
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_EN__MSK      0x04
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_EN__REG      \
BMG160_BGW_SPI3_WDT_ADDR

 
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SEL__POS     1
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SEL__LEN     1
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SEL__MSK     0x02
#define BMG160_BGW_SPI3_WDT_ADDR_I2C_WDT_SEL__REG     \
BMG160_BGW_SPI3_WDT_ADDR

#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__POS            0
#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__LEN            1
#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__MSK            0x01
#define BMG160_BGW_SPI3_WDT_ADDR_SPI3__REG            \
BMG160_BGW_SPI3_WDT_ADDR

#define BMG160_SELF_TEST_ADDR_RATEOK__POS            4
#define BMG160_SELF_TEST_ADDR_RATEOK__LEN            1
#define BMG160_SELF_TEST_ADDR_RATEOK__MSK            0x10
#define BMG160_SELF_TEST_ADDR_RATEOK__REG            \
BMG160_SELF_TEST_ADDR

#define BMG160_SELF_TEST_ADDR_BISTFAIL__POS          2
#define BMG160_SELF_TEST_ADDR_BISTFAIL__LEN          1
#define BMG160_SELF_TEST_ADDR_BISTFAIL__MSK          0x04
#define BMG160_SELF_TEST_ADDR_BISTFAIL__REG          \
BMG160_SELF_TEST_ADDR

#define BMG160_SELF_TEST_ADDR_BISTRDY__POS           1
#define BMG160_SELF_TEST_ADDR_BISTRDY__LEN           1
#define BMG160_SELF_TEST_ADDR_BISTRDY__MSK           0x02
#define BMG160_SELF_TEST_ADDR_BISTRDY__REG           \
BMG160_SELF_TEST_ADDR

#define BMG160_SELF_TEST_ADDR_TRIGBIST__POS          0
#define BMG160_SELF_TEST_ADDR_TRIGBIST__LEN          1
#define BMG160_SELF_TEST_ADDR_TRIGBIST__MSK          0x01
#define BMG160_SELF_TEST_ADDR_TRIGBIST__REG          \
BMG160_SELF_TEST_ADDR

#define BMG160_FIFO_CGF1_ADDR_TAG__POS     7
#define BMG160_FIFO_CGF1_ADDR_TAG__LEN     1
#define BMG160_FIFO_CGF1_ADDR_TAG__MSK     0x80
#define BMG160_FIFO_CGF1_ADDR_TAG__REG     BMG160_FIFO_CGF1_ADDR

#define BMG160_FIFO_CGF1_ADDR_WML__POS     0
#define BMG160_FIFO_CGF1_ADDR_WML__LEN     7
#define BMG160_FIFO_CGF1_ADDR_WML__MSK     0x7F
#define BMG160_FIFO_CGF1_ADDR_WML__REG     BMG160_FIFO_CGF1_ADDR

#define BMG160_FIFO_CGF0_ADDR_MODE__POS         6
#define BMG160_FIFO_CGF0_ADDR_MODE__LEN         2
#define BMG160_FIFO_CGF0_ADDR_MODE__MSK         0xC0
#define BMG160_FIFO_CGF0_ADDR_MODE__REG         BMG160_FIFO_CGF0_ADDR

#define BMG160_FIFO_CGF0_ADDR_DATA_SEL__POS     0
#define BMG160_FIFO_CGF0_ADDR_DATA_SEL__LEN     2
#define BMG160_FIFO_CGF0_ADDR_DATA_SEL__MSK     0x03
#define BMG160_FIFO_CGF0_ADDR_DATA_SEL__REG     BMG160_FIFO_CGF0_ADDR

 
#define BMG160_OFC1_ADDR_OFFSET_X__POS       6
#define BMG160_OFC1_ADDR_OFFSET_X__LEN       2
#define BMG160_OFC1_ADDR_OFFSET_X__MSK       0xC0
#define BMG160_OFC1_ADDR_OFFSET_X__REG       BMG160_OFC1_ADDR

#define BMG160_OFC1_ADDR_OFFSET_Y__POS       3
#define BMG160_OFC1_ADDR_OFFSET_Y__LEN       3
#define BMG160_OFC1_ADDR_OFFSET_Y__MSK       0x38
#define BMG160_OFC1_ADDR_OFFSET_Y__REG       BMG160_OFC1_ADDR

#define BMG160_OFC1_ADDR_OFFSET_Z__POS       0
#define BMG160_OFC1_ADDR_OFFSET_Z__LEN       3
#define BMG160_OFC1_ADDR_OFFSET_Z__MSK       0x07
#define BMG160_OFC1_ADDR_OFFSET_Z__REG       BMG160_OFC1_ADDR

#define BMG160_TRIM_GP0_ADDR_GP0__POS            4
#define BMG160_TRIM_GP0_ADDR_GP0__LEN            4
#define BMG160_TRIM_GP0_ADDR_GP0__MSK            0xF0
#define BMG160_TRIM_GP0_ADDR_GP0__REG            BMG160_TRIM_GP0_ADDR

#define BMG160_TRIM_GP0_ADDR_OFFSET_X__POS       2
#define BMG160_TRIM_GP0_ADDR_OFFSET_X__LEN       2
#define BMG160_TRIM_GP0_ADDR_OFFSET_X__MSK       0x0C
#define BMG160_TRIM_GP0_ADDR_OFFSET_X__REG       BMG160_TRIM_GP0_ADDR

#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__POS       1
#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__LEN       1
#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__MSK       0x02
#define BMG160_TRIM_GP0_ADDR_OFFSET_Y__REG       BMG160_TRIM_GP0_ADDR

#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__POS       0
#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__LEN       1
#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__MSK       0x01
#define BMG160_TRIM_GP0_ADDR_OFFSET_Z__REG       BMG160_TRIM_GP0_ADDR

#define BMG160_X_AXIS           0
#define BMG160_Y_AXIS           1
#define BMG160_Z_AXIS           2

#define BMG160_MODE_NORMAL              0
#define BMG160_MODE_DEEPSUSPEND         1
#define BMG160_MODE_SUSPEND             2
#define BMG160_MODE_FASTPOWERUP			3
#define BMG160_MODE_ADVANCEDPOWERSAVING 4

#define BMG160_GET_BITSLICE(regvar, bitname)\
((regvar & bitname##__MSK) >> bitname##__POS)

#define BMG160_SET_BITSLICE(regvar, bitname, val)\
((regvar&~bitname##__MSK)|((val<<bitname##__POS)&bitname##__MSK))

#define BMG160_NULL                             0
#define BMG160_DISABLE                          0
#define BMG160_ENABLE                           1
#define BMG160_OFF                              0
#define BMG160_ON                               1


#define BMG160_TURN1                            0
#define BMG160_TURN2                            1

#define BMG160_INT1                             0
#define BMG160_INT2                             1

#define BMG160_SLOW_OFFSET                      0
#define BMG160_AUTO_OFFSET                      1
#define BMG160_FAST_OFFSET                      2
#define BMG160_S_TAP                            0
#define BMG160_D_TAP                            1
#define BMG160_INT1_DATA                        0
#define BMG160_INT2_DATA                        1
#define BMG160_TAP_UNFILT_DATA                   0
#define BMG160_HIGH_UNFILT_DATA                  1
#define BMG160_CONST_UNFILT_DATA                 2
#define BMG160_ANY_UNFILT_DATA                   3
#define BMG160_SHAKE_UNFILT_DATA                 4
#define BMG160_SHAKE_TH                         0
#define BMG160_SHAKE_TH2                        1
#define BMG160_AUTO_OFFSET_WL                   0
#define BMG160_FAST_OFFSET_WL                   1
#define BMG160_I2C_WDT_EN                       0
#define BMG160_I2C_WDT_SEL                      1
#define BMG160_EXT_MODE                         0
#define BMG160_EXT_PAGE                         1
#define BMG160_START_ADDR                       0
#define BMG160_STOP_ADDR                        1
#define BMG160_SLOW_CMD                         0
#define BMG160_FAST_CMD                         1
#define BMG160_TRIM_VRA                         0
#define BMG160_TRIM_VRD                         1
#define BMG160_LOGBIT_EM                        0
#define BMG160_LOGBIT_VM                        1
#define BMG160_GP0                              0
#define BMG160_GP1                              1
#define BMG160_LOW_SPEED                        0
#define BMG160_HIGH_SPEED                       1
#define BMG160_DRIVE_OFFSET_P                   0
#define BMG160_DRIVE_OFFSET_N                   1
#define BMG160_TEST_MODE_EN                     0
#define BMG160_TEST_MODE_REG                    1
#define BMG160_IBIAS_DRIVE_TRIM                 0
#define BMG160_IBIAS_RATE_TRIM                  1
#define BMG160_BAA_MODE                         0
#define BMG160_BMA_MODE                         1
#define BMG160_PI_KP                            0
#define BMG160_PI_KI                            1


#define C_BMG160_SUCCESS						0
#define C_BMG160_FAILURE						1

#define BMG160_SPI_RD_MASK                      0x80
#define BMG160_READ_SET                         0x01

#define BMG160_SHIFT_1_POSITION                 1
#define BMG160_SHIFT_2_POSITION                 2
#define BMG160_SHIFT_3_POSITION                 3
#define BMG160_SHIFT_4_POSITION                 4
#define BMG160_SHIFT_5_POSITION                 5
#define BMG160_SHIFT_6_POSITION                 6
#define BMG160_SHIFT_7_POSITION                 7
#define BMG160_SHIFT_8_POSITION                 8
#define BMG160_SHIFT_12_POSITION                12

#define         C_BMG160_Null_U8X                              0
#define         C_BMG160_Zero_U8X                              0
#define         C_BMG160_One_U8X                               1
#define         C_BMG160_Two_U8X                               2
#define         C_BMG160_Three_U8X                             3
#define         C_BMG160_Four_U8X                              4
#define         C_BMG160_Five_U8X                              5
#define         C_BMG160_Six_U8X                               6
#define         C_BMG160_Seven_U8X                             7
#define         C_BMG160_Eight_U8X                             8
#define         C_BMG160_Nine_U8X                              9
#define         C_BMG160_Ten_U8X                               10
#define         C_BMG160_Eleven_U8X                            11
#define         C_BMG160_Twelve_U8X                            12
#define         C_BMG160_Thirteen_U8X                          13
#define         C_BMG160_Fifteen_U8X                           15
#define         C_BMG160_Sixteen_U8X                           16
#define         C_BMG160_TwentyTwo_U8X                         22
#define         C_BMG160_TwentyThree_U8X                       23
#define         C_BMG160_TwentyFour_U8X                        24
#define         C_BMG160_TwentyFive_U8X                        25
#define         C_BMG160_ThirtyTwo_U8X                         32
#define         C_BMG160_Hundred_U8X                           100
#define         C_BMG160_OneTwentySeven_U8X                    127
#define         C_BMG160_OneTwentyEight_U8X                    128
#define         C_BMG160_TwoFiftyFive_U8X                      255
#define         C_BMG160_TwoFiftySix_U16X                      256

#define E_BMG160_NULL_PTR               (char)(-127)
#define E_BMG160_COMM_RES               (char)(-1)
#define E_BMG160_OUT_OF_RANGE           (signed char)(-2)

#define C_BMG160_No_Filter_U8X			0
#define	C_BMG160_BW_230Hz_U8X			1
#define	C_BMG160_BW_116Hz_U8X			2
#define	C_BMG160_BW_47Hz_U8X			3
#define	C_BMG160_BW_23Hz_U8X			4
#define	C_BMG160_BW_12Hz_U8X			5
#define	C_BMG160_BW_64Hz_U8X			6
#define	C_BMG160_BW_32Hz_U8X			7

#define C_BMG160_No_AutoSleepDur_U8X	0
#define	C_BMG160_4ms_AutoSleepDur_U8X	1
#define	C_BMG160_5ms_AutoSleepDur_U8X	2
#define	C_BMG160_8ms_AutoSleepDur_U8X	3
#define	C_BMG160_10ms_AutoSleepDur_U8X	4
#define	C_BMG160_15ms_AutoSleepDur_U8X	5
#define	C_BMG160_20ms_AutoSleepDur_U8X	6
#define	C_BMG160_40ms_AutoSleepDur_U8X	7




#define BMG160_WR_FUNC_PTR char (*bus_write)\
(unsigned char, unsigned char, unsigned char *, unsigned char)
#define BMG160_RD_FUNC_PTR char (*bus_read)\
(unsigned char, unsigned char, unsigned char *, unsigned char)
#define BMG160_BRD_FUNC_PTR char (*burst_read)\
(unsigned char, unsigned char, unsigned char *, BMG160_S32)
#define BMG160_MDELAY_DATA_TYPE BMG160_S32




struct bmg160_data_t {
		BMG160_S16 datax;
		BMG160_S16 datay;
		BMG160_S16 dataz;
		char intstatus[5];
};


struct bmg160_offset_t {
		BMG160_U16 datax;
		BMG160_U16 datay;
		BMG160_U16 dataz;
};


struct bmg160_t {
		unsigned char chip_id;
		unsigned char dev_addr;
		BMG160_BRD_FUNC_PTR;
		BMG160_WR_FUNC_PTR;
		BMG160_RD_FUNC_PTR;
		void(*delay_msec)(BMG160_MDELAY_DATA_TYPE);
};

BMG160_RETURN_FUNCTION_TYPE bmg160_init(struct bmg160_t *p_bmg160);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_dataX(BMG160_S16 *data_x);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_dataY(BMG160_S16 *data_y);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_dataZ(BMG160_S16 *data_z);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_dataXYZ(struct bmg160_data_t *data);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_dataXYZI(struct bmg160_data_t *data);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_Temperature(unsigned char *temperature);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_FIFO_data_reg\
(unsigned char *FIFO_data);
BMG160_RETURN_FUNCTION_TYPE bmg160_read_register(unsigned char addr,\
unsigned char *data, unsigned char len);
BMG160_RETURN_FUNCTION_TYPE bmg160_burst_read(unsigned char addr,\
unsigned char reg, unsigned char *data, BMG160_S32 len);
BMG160_RETURN_FUNCTION_TYPE bmg160_write_register(unsigned char addr,\
unsigned char *data, unsigned char len);

BMG160_RETURN_FUNCTION_TYPE bmg160_get_interrupt_status_reg_0\
(unsigned char *status0_data);

BMG160_RETURN_FUNCTION_TYPE bmg160_get_interrupt_status_reg_1\
(unsigned char *status1_data);

BMG160_RETURN_FUNCTION_TYPE bmg160_get_interrupt_status_reg_2\
(unsigned char *status2_data);

BMG160_RETURN_FUNCTION_TYPE bmg160_get_interrupt_status_reg_3\
(unsigned char *status3_data);

BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifostatus_reg\
(unsigned char *fifo_status);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_range_reg\
(unsigned char *range);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_range_reg\
(unsigned char range);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_res\
(unsigned char *high_res);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_res\
(unsigned char high_res);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_bw(unsigned char *bandwidth);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_bw(unsigned char bandwidth);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_pmu_ext_tri_sel\
(unsigned char *pwu_ext_tri_sel);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_pmu_ext_tri_sel\
(unsigned char pwu_ext_tri_sel);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_bw\
(unsigned char *high_bw);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_bw\
(unsigned char high_bw);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_shadow_dis\
(unsigned char *shadow_dis);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_shadow_dis\
(unsigned char shadow_dis);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_soft_reset(void);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_data_enable(unsigned char *data_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_data_enable(unsigned char data_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_enable(unsigned char *fifo_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_enable(unsigned char fifo_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset_enable\
(unsigned char mode, unsigned char *offset_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_enable\
(unsigned char mode, unsigned char offset_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int_od\
(unsigned char param, unsigned char *int_od);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int_od\
(unsigned char param, unsigned char int_od);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int_lvl\
(unsigned char param, unsigned char *int_lvl);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int_lvl\
(unsigned char param, unsigned char int_lvl);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int1_high\
(unsigned char *int1_high);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int1_high\
(unsigned char int1_high);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int1_any\
(unsigned char *int1_any);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int1_any\
(unsigned char int1_any);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int_data\
(unsigned char axis, unsigned char *int_data);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int_data\
(unsigned char axis, unsigned char int_data);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int2_offset\
(unsigned char axis, unsigned char *int2_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int2_offset\
(unsigned char axis, unsigned char int2_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int1_offset\
(unsigned char axis, unsigned char *int1_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int1_offset\
(unsigned char axis, unsigned char int1_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int_fifo(unsigned char *int_fifo);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int_fifo\
(unsigned char axis, unsigned char int_fifo);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int2_high\
(unsigned char *int2_high);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int2_high\
(unsigned char int2_high);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int2_any\
(unsigned char *int2_any);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int2_any\
(unsigned char int2_any);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset_unfilt\
(unsigned char param, unsigned char *offset_unfilt);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_unfilt\
(unsigned char param, unsigned char offset_unfilt);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_unfilt_data\
(unsigned char param, unsigned char *unfilt_data);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_unfilt_data\
(unsigned char param, unsigned char unfilt_data);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_th\
(unsigned char *any_th);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_th\
(unsigned char any_th);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_awake_dur\
(unsigned char *awake_dur);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_awake_dur\
(unsigned char awake_dur);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_dursample\
(unsigned char *dursample);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_dursample\
(unsigned char dursample);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_any_en_ch\
(unsigned char channel, unsigned char *data);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_any_en_ch\
(unsigned char channel, unsigned char data);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_watermark_enable\
(unsigned char *fifo_wn_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_watermark_enable\
(unsigned char fifo_wn_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_reset_int\
(unsigned char reset_int);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_reset\
(unsigned char offset_reset);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_latch_status\
(unsigned char *latch_status);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_latch_status\
(unsigned char latch_status);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_latch_int\
(unsigned char *latch_int);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_latch_int\
(unsigned char latch_int);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_hy\
(unsigned char channel, unsigned char *high_hy);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_hy\
(unsigned char channel, unsigned char high_hy);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_th\
(unsigned char channel, unsigned char *high_th);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_th\
(unsigned char channel, unsigned char high_th);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_en_ch\
(unsigned char channel, unsigned char *high_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_en_ch\
(unsigned char channel, unsigned char high_en);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_high_dur_ch\
(unsigned char channel, unsigned char *high_dur);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_high_dur_ch\
(unsigned char channel, unsigned char high_dur);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_th\
(unsigned char *offset_th);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_th\
(unsigned char offset_th);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_dur\
(unsigned char *offset_dur);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_dur\
(unsigned char offset_dur);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_slow_offset_en_ch\
(unsigned char channel, unsigned char *slow_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_slow_offset_en_ch\
(unsigned char channel, unsigned char slow_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset_wl\
(unsigned char channel, unsigned char *offset_wl);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset_wl\
(unsigned char channel, unsigned char offset_wl);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fast_offset_en\
(unsigned char fast_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fast_offset_en_ch\
(unsigned char *fast_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fast_offset_en_ch\
(unsigned char channel, unsigned char fast_offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_enable_fast_offset(void);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_remain\
(unsigned char *nvm_remain);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_load\
(unsigned char nvm_load);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_rdy\
(unsigned char *nvm_rdy);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_prog_trig\
(unsigned char prog_trig);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_nvm_prog_mode\
(unsigned char *prog_mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_nvm_prog_mode\
(unsigned char prog_mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_i2c_wdt\
(unsigned char i2c_wdt, unsigned char *prog_mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_i2c_wdt\
(unsigned char i2c_wdt, unsigned char prog_mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_spi3(unsigned char *spi3);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_spi3(unsigned char spi3);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_tag(unsigned char *tag);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_tag(unsigned char tag);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_watermarklevel\
(unsigned char *water_mark_level);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_watermarklevel\
(unsigned char water_mark_level);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_mode\
(unsigned char *mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_mode(unsigned char mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_data_sel\
(unsigned char *data_sel);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_fifo_data_sel\
(unsigned char data_sel);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_offset\
(unsigned char axis, BMG160_S16 *offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_offset\
(unsigned char axis, BMG160_S16 offset);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_gp\
(unsigned char param, unsigned char *value);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_gp\
(unsigned char param, unsigned char value);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_framecount\
(unsigned char *fifo_framecount);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_fifo_overrun\
(unsigned char *fifo_overrun);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int2_fifo\
(unsigned char *int_fifo);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_int1_fifo\
(unsigned char *int_fifo);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int2_fifo\
(unsigned char fifo_int2);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_int1_fifo\
(unsigned char fifo_int1);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_mode(unsigned char *Mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_set_mode(unsigned char Mode);
BMG160_RETURN_FUNCTION_TYPE bmg160_selftest(unsigned char *result);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_autosleepdur(unsigned char *duration);
/**\brief This API is used to set duration
 *
 *
 *
 *
 *  \param unsigned char duration:
 *          Value to be written passed as a parameter
 *		   unsigned char bandwith:
 *			Value to be written passed as a parameter
 *
 *  \return communication results
 *
 *
 *****************************************************************************/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_autosleepdur(unsigned char duration, \
unsigned char bandwith);
BMG160_RETURN_FUNCTION_TYPE bmg160_get_sleepdur(unsigned char *duration);
/**\brief This API is used to set duration
 *
 *
 *
 *
 *  \param unsigned char duration:
 *          Value to be written passed as a parameter
 *
 *
 *
 *  \return communication results
 *
 *
 *****************************************************************************/
BMG160_RETURN_FUNCTION_TYPE bmg160_set_sleepdur(unsigned char duration);
#endif
