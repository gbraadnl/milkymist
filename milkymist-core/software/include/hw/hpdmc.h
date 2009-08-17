/*
 * Milkymist VJ SoC (Software support library)
 * Copyright (C) 2007, 2008, 2009 Sebastien Bourdeauducq
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 3 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 */

#ifndef __HW_HPDMC_H
#define __HW_HPDMC_H

#include <hw/common.h>

#define CSR_HPDMC_SYSTEM	MMPTR(0x80002000)

#define HPDMC_SYSTEM_BYPASS	(0x01)
#define HPDMC_SYSTEM_RESET	(0x02)
#define HPDMC_SYSTEM_CKE	(0x04)

#define CSR_HPDMC_BYPASS	MMPTR(0x80002004)

#define HPDMC_BYPASS_CS		(0x01)
#define HPDMC_BYPASS_WE		(0x02)
#define HPDMC_BYPASS_CAS	(0x04)
#define HPDMC_BYPASS_RAS	(0x08)
#define HPDMC_BYPASS_A_S	(4)
#define HPDMC_BYPASS_BA_S	(17)

#define CSR_HPDMC_TIMING	MMPTR(0x80002008)

#define HPDMC_TIMING_TRP_S	(0)
#define HPDMC_TIMING_TRCD_S	(3)
#define HPDMC_TIMING_CL3	(0x40)
#define HPDMC_TIMING_TREFI_S	(7)
#define HPDMC_TIMING_TRFC_S	(18)
#define HPDMC_TIMING_TWR_S	(22)

#define CSR_HPDMC_IODELAY	MMPTR(0x8000200C)

#define HPDMC_IDELAY_RST	(0x01)
#define HPDMC_IDELAY_CE		(0x02)
#define HPDMC_IDELAY_INC	(0x04)

#define HPDMC_DQSDELAY_CE	(0x08)
#define HPDMC_DQSDELAY_INC	(0x10)
#define HPDMC_DQSDELAY_RDY	(0x20)

#define HPDMC_PLL1_LOCKED	(0x40)
#define HPDMC_PLL2_LOCKED	(0x80)

#define SDRAM_BASE		(0x40000000)

#endif /* __HW_HPDMC_H */
