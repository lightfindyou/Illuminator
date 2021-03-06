/*
 * Generic Generic NCR5380 driver defines
 *
 * Copyright 1993, Drew Eckhardt
 *	Visionary Computing
 *	(Unix and Linux consulting and custom programming)
 *	drew@colorado.edu
 *      +1 (303) 440-4894
 *
 * NCR53C400 extensions (c) 1994,1995,1996, Kevin Lentin
 *    K.Lentin@cs.monash.edu.au
 */

#ifndef GENERIC_NCR5380_H
#define GENERIC_NCR5380_H

#ifdef CONFIG_SCSI_GENERIC_NCR53C400
#define BIOSPARAM
#define NCR5380_BIOSPARAM generic_NCR5380_biosparam
#else
#define NCR5380_BIOSPARAM NULL
#endif

#define __STRVAL(x) #x
#define STRVAL(x) __STRVAL(x)

#ifndef SCSI_G_NCR5380_MEM
#define DRV_MODULE_NAME "g_NCR5380"

#define NCR5380_map_type int
#define NCR5380_map_name port

#ifdef CONFIG_SCSI_GENERIC_NCR53C400
#define NCR5380_region_size 16
#else
#define NCR5380_region_size 8
#endif

#define NCR5380_read(reg) \
	inb(instance->io_port + (reg))
#define NCR5380_write(reg, value) \
	outb(value, instance->io_port + (reg))

#define NCR5380_implementation_fields \
	int c400_ctl_status; \
	int c400_blk_cnt; \
	int c400_host_buf; \
	int io_width;

#else 
/* therefore SCSI_G_NCR5380_MEM */
#define DRV_MODULE_NAME "g_NCR5380_mmio"

#define NCR5380_map_type unsigned long
#define NCR5380_map_name base
#define NCR53C400_mem_base 0x3880
#define NCR53C400_host_buffer 0x3900
#define NCR5380_region_size 0x3a00

#define NCR5380_read(reg) \
	readb(((struct NCR5380_hostdata *)shost_priv(instance))->iomem + \
	      NCR53C400_mem_base + (reg))
#define NCR5380_write(reg, value) \
	writeb(value, ((struct NCR5380_hostdata *)shost_priv(instance))->iomem + \
	       NCR53C400_mem_base + (reg))

#define NCR5380_implementation_fields \
	void __iomem *iomem; \
	int c400_ctl_status; \
	int c400_blk_cnt; \
	int c400_host_buf;

#endif

#define NCR5380_dma_xfer_len(instance, cmd, phase) \
        generic_NCR5380_dma_xfer_len(cmd)

#define NCR5380_intr generic_NCR5380_intr
#define NCR5380_queue_command generic_NCR5380_queue_command
#define NCR5380_abort generic_NCR5380_abort
#define NCR5380_bus_reset generic_NCR5380_bus_reset
#define NCR5380_pread generic_NCR5380_pread
#define NCR5380_pwrite generic_NCR5380_pwrite
#define NCR5380_info generic_NCR5380_info
#define NCR5380_show_info generic_NCR5380_show_info

#define BOARD_NCR5380	0
#define BOARD_NCR53C400	1
#define BOARD_NCR53C400A 2
#define BOARD_DTC3181E	3
#define BOARD_HP_C2502	4

#endif /* GENERIC_NCR5380_H */

