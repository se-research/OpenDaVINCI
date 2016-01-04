/*
 * CAN driver for PEAK System micro-CAN based adapters
 *
 * Copyright (C) 2003-2011 PEAK System-Technik GmbH
 * Copyright (C) 2011-2013 Stephane Grosjean <s.grosjean@peak-system.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published
 * by the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 */
#ifndef PUCAN_H
#define PUCAN_H

/* uCAN commands opcodes list (low-order 10 bits) */
#define PUCAN_CMD_NOP			0x000
#define PUCAN_CMD_RESET_MODE		0x001
#define PUCAN_CMD_NORMAL_MODE		0x002
#define PUCAN_CMD_LISTEN_ONLY_MODE	0x003
#define PUCAN_CMD_TIMING_SLOW		0x004
#define PUCAN_CMD_TIMING_FAST		0x005
#define PUCAN_CMD_FILTER_STD		0x008
#define PUCAN_CMD_TX_ABORT		0x009
#define PUCAN_CMD_WR_ERR_CNT		0x00a
#define PUCAN_CMD_RX_FRAME_ENABLE	0x00b
#define PUCAN_CMD_RX_FRAME_DISABLE	0x00c

#define PUCAN_CMD_SET_ERR_GEN		0x00d
#define PUCAN_CMD_END_OF_COLLECTION	0x3ff

/* uCAN received messages list */
#define PUCAN_MSG_CAN_RX		0x0001
#define PUCAN_MSG_ERROR			0x0002
#define PUCAN_MSG_STATUS		0x0003
#define PUCAN_MSG_BUSLOAD		0x0004
#define PUCAN_MSG_CAN_TX		0x1000

/* uCAN command common header */
#define PUCAN_CMD_OPCODE(c)		((c)->opcode_channel & 0x3ff)
#define PUCAN_CMD_CHANNEL(c)		((c)->opcode_channel >> 12)
#define PUCAN_CMD_OPCODE_CHANNEL(c, o)	cpu_to_le16(((c) << 12) | ((o) & 0x3ff))

struct __packed pucan_command {
	u16	opcode_channel;
	u16	args[3];
};

/* uCAN TIMING_SLOW command fields */
#define PUCAN_TSLOW_SJW_T(s, t)		(((s) & 0xf) | ((!!(t)) << 7))
#define PUCAN_TSLOW_TSEG2(t)		((t) & 0xf)
#define PUCAN_TSLOW_TSEG1(t)		((t) & 0x3f)
#define PUCAN_TSLOW_BRP(b)		cpu_to_le16((b) & 0x3ff)

struct __packed pucan_timing_slow {
	u16	opcode_channel;

	u8	ewl;		/* Error Warning limit */
	u8	sjw_t;		/* Sync Jump Width + Triple sampling */
	u8	tseg2;		/* Timing SEGment 2 */
	u8	tseg1;		/* Timing SEGment 1 */

	u16	brp;		/* BaudRate Prescaler */
};

/* uCAN TIMING_FAST command fields */
#define PUCAN_TFAST_SJW(s)		((s) & 0x3)
#define PUCAN_TFAST_TSEG2(t)		((t) & 0x7)
#define PUCAN_TFAST_TSEG1(t)		((t) & 0xf)
#define PUCAN_TFAST_BRP(b)		cpu_to_le16((b) & 0x3ff)

struct __packed pucan_timing_fast {
	u16	opcode_channel;

	u8	unused;
	u8	sjw;		/* Sync Jump Width */
	u8	tseg2;		/* Timing SEGment 2 */
	u8	tseg1;		/* Timing SEGment 1 */

	u16	brp;		/* BaudRate Prescaler */
};

/* uCAN FILTER_STD command fields */
#define PUCAN_FLTSTD_ROW_IDX_BITS	6

struct __packed pucan_filter_std {
	u16	opcode_channel;

	u16	idx;
	u32	mask;		/* CAN-ID bitmask in idx range */
};

/* uCAN WR_ERR_CNT command fields */
#define PUCAN_WRERRCNT_TE		0x4000	/* Tx error cntr write Enable */
#define PUCAN_WRERRCNT_RE		0x8000	/* Rx error cntr write Enable */

struct __packed pucan_wr_err_cnt {
	u16	opcode_channel;

	u16	sel_mask;
	u8	tx_counter;	/* Tx error counter new value */
	u8	rx_counter;	/* Rx error counter new value */

	u16	unused;
};

/* uCAN RX_FRAME_ENABLE command fields */
#define PUCAN_FLTEXT_ERROR		0x0001
#define PUCAN_FLTEXT_BUSLOAD		0x0002

struct __packed pucan_filter_ext {
	u16	opcode_channel;

	u16	ext_mask;
	u32	unused;
};

/* uCAN received messages global format */
struct __packed pucan_msg {
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
};

/* uCAN flags for CAN/CANFD messages */
#define PUCAN_MSG_API_SRR		0x80
#define PUCAN_MSG_ERROR_STATE_IND	0x40	/* error state indicator */
#define PUCAN_MSG_BITRATE_SWITCH	0x20	/* bitrate switch */
#define PUCAN_MSG_EXT_DATA_LEN		0x10	/* extended data length */
#define PUCAN_MSG_SINGLE_SHOT		0x08
#define PUCAN_MSG_HW_SRR		0x04
#define PUCAN_MSG_EXT_ID		0x02
#define PUCAN_MSG_RTR			0x01

#define PUCAN_MSG_CHANNEL(m)		((m)->channel_dlc & 0xf)
#define PUCAN_MSG_DLC(m)		((m)->channel_dlc >> 4)

struct __packed pucan_rx_msg {
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	__le32	tag_low;
	__le32	tag_high;
	u8	channel_dlc;
	u8	client;
	__le16	flags;
	__le32	can_id;
	u8	d[0];
};

/* uCAN error types */
#define PUCAN_ERMSG_BIT_ERROR		0
#define PUCAN_ERMSG_FORM_ERROR		1
#define PUCAN_ERMSG_STUFF_ERROR		2
#define PUCAN_ERMSG_OTHER_ERROR		3
#define PUCAN_ERMSG_ERR_CNT_DEC		4

#define PUCAN_ERMSG_CHANNEL(e)		((e)->channel_type_d & 0x0f)
#define PUCAN_ERMSG_ERRTYPE(e)		(((e)->channel_type_d >> 4) & 0x07)
#define PUCAN_ERMSG_D(e)		((e)->channel_type_d & 0x80)

#define PUCAN_ERMSG_ERRCODE(e)		((e)->code_g & 0x7f)
#define PUCAN_ERMSG_G(e)		((e)->code_g & 0x80)

struct __packed pucan_error_msg {
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	u8	channel_type_d;
	u8	code_g;
	u8	tx_err_cnt;
	u8	rx_err_cnt;
};

#define PUCAN_STMSG_CHANNEL(e)		((e)->channel_p_w_b & 0x0f)
#define PUCAN_STMSG_PASSIVE(e)		((e)->channel_p_w_b & 0x20)
#define PUCAN_STMSG_WARNING(e)		((e)->channel_p_w_b & 0x40)
#define PUCAN_STMSG_BUSOFF(e)		((e)->channel_p_w_b & 0x80)

struct __packed pucan_status_msg {
	__le16	size;
	__le16	type;
	__le32	ts_low;
	__le32	ts_high;
	u8	channel_p_w_b;
	u8	unused[3];
};

/* uCAN transmitted message format */
#define PUCAN_MSG_CHANNEL_DLC(c, d)	(((c) & 0xf) | ((d) << 4))

struct __packed pucan_tx_msg {
	__le16	size;
	__le16	type;
	__le32	tag_low;
	__le32	tag_high;
	u8	channel_dlc;
	u8	client;
	u16	flags;
	__le32	can_id;
	u8	d[0];
};

#endif
