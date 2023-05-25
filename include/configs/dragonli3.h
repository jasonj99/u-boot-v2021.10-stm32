/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2023, JasonJ - All Rights Reserved
 * Author(s): JasonJ, <jasonj@live.cn>.
 * 
 * based on
 * Copyright (C) 2016, STMicroelectronics - All Rights Reserved
 * Author(s): Vikas Manocha, <vikas.manocha@st.com> for STMicroelectronics.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

/* For booting Linux, use the first 6MB of memory */
#define CONFIG_SYS_BOOTMAPSZ		SZ_4M + SZ_2M

#define CONFIG_SYS_FLASH_BASE		0x08000000
#define CONFIG_SYS_INIT_SP_ADDR		0x20050000

#ifdef CONFIG_SUPPORT_SPL
#define CONFIG_SYS_LOAD_ADDR		0x08008000
#else
#define CONFIG_SYS_LOAD_ADDR		0xC0400000
#define CONFIG_LOADADDR			    0xC0400000
#endif

/*
 * Configuration of the external SDRAM memory
 */

#define CONFIG_SYS_MAX_FLASH_SECT	8
#define CONFIG_SYS_MAX_FLASH_BANKS	1

#define CONFIG_STM32_FLASH

#define CONFIG_DW_GMAC_DEFAULT_DMA_PBL	(8)
#define CONFIG_DW_ALTDESCRIPTOR

#define CONFIG_SYS_HZ_CLOCK		    1000000	/* Timer is clocked at 1MHz */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_SYS_CBSIZE		    	SZ_1K

#define CONFIG_SYS_MALLOC_LEN			SZ_1M

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0)


#define CONFIG_ETHADDR                  AA:CC:DD:11:22:33
#define CONFIG_NETMASK                  255.255.255.0
#define CONFIG_IPADDR                   192.168.10.234
#define CONFIG_GATEWAYIP                192.168.10.1
#define SERVERIP                		192.168.10.30

#ifndef MK_STR
#define STR1(x)     	#x
#define MK_STR(x)       STR1(x)
#endif

#define SPI_IMG_OFFSET               	SZ_1M  /* Kernel is stored in SPI Flash (offset at 128KB) */
#define SPI_FDT_OFFSET                  SZ_32K    /* the first 8KB is used to save env in SPI Flash */

#define CUST_ENV_SETTINGS                                      \
        "serverip=192.168.10.128\0"                            \
        "args=setenv bootargs " CONFIG_BOOTARGS "\0"    	   \
        "image=zImage\0"                                       \
        "spiaddr_img=" MK_STR(SPI_IMG_OFFSET) "\0" 		       \
		"spiaddr_fdt=" MK_STR(SPI_FDT_OFFSET) "\0"   		   \
        "spisize=0\0"	                                       \
        "spiprobe=sf probe\0"                                  \
        "addip=setenv bootargs ${bootargs}"                    \
        " ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}:${hostname}:eth0:off\0"  \
        "flashboot=run args addip;run spiprobe;"               \
        " sf read ${kernel_addr_r} ${spiaddr} ${spisize};"     \
        " bootm ${kernel_addr_r}\0"                            \
        "netboot="                                             \
        " tftp ${kernel_addr_r} ${image};"                     \
        " tftp ${fdt_addr_r} ${fdtfile};"                      \
        " run args addip;"                                     \
        " bootz ${kernel_addr_r} - ${fdt_addr_r}\0"            \
        "update=run spiprobe;" 								   \
		" tftp ${fdt_addr_r} ${fdtfile};"					   \
        " sf erase ${spiaddr_fdt} +${filesize};"               \
        " sf write ${fdt_addr_r} ${spiaddr_fdt} ${filesize};"  \
		" tftp ${kernel_addr_r} ${image};"					   \
        " sf erase ${spiaddr_img} +${filesize};"               \
        " sf write ${kernel_addr_r} ${spiaddr_img} ${filesize}\0"

#include <config_distro_bootcmd.h>
#define CONFIG_EXTRA_ENV_SETTINGS				\
			CUST_ENV_SETTINGS					\
			"kernel_addr_r=0xC0000000\0"		\
			"fdtfile=dragonli3.dtb\0"	        \
			"fdt_addr_r=0xC0408000\0"		    \
			"scriptaddr=0xC0418000\0"		    \
			"pxefile_addr_r=0xC0428000\0"       \
			"ramdisk_addr_r=0xC0438000\0"		\
			BOOTENV

#define CONFIG_DISPLAY_BOARDINFO

/* NOTE:
 * the spi flash IS nor1 NOT nor0, even the flash device is named "nor0" in dts
 * the u-boot command "mtd" always show it is "nor1",
 * may be "nor0" is for the stm32's internal flash
 */
#ifndef CONFIG_MTDIDS_DEFAULT
#define CONFIG_MTDIDS_DEFAULT   "nor0=w25q128"
#endif

#ifndef CONFIG_MTDPARTS_DEFAULT
#define CONFIG_MTDPARTS_DEFAULT "mtdparts=w25q128:32K(u-boot-env),128k(kernel-dtb),864k(reserved1),3m(kernel),8m(rootfs),4m(reserved2)"
#endif

/* For SPL */
#ifdef CONFIG_SUPPORT_SPL
#define CONFIG_SPL_STACK		    CONFIG_SYS_INIT_SP_ADDR
#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)
#define CONFIG_SYS_SPL_LEN		    0x00008000
#define CONFIG_SYS_UBOOT_START		0x080083FD
#define CONFIG_SYS_UBOOT_BASE		(CONFIG_SYS_FLASH_BASE + CONFIG_SYS_SPL_LEN)

/* DT blob (fdt) address */
#define CONFIG_SYS_FDT_BASE		    (CONFIG_SYS_FLASH_BASE + 0x1C0000)
#endif
/* For SPL ends */

/* For splashcreen */

#endif /* __CONFIG_H */
