/*
 *  DPTechnics DPT-Module machine configuration
 *
 *  (C) 2015 Daan Pape, DPTechnics <daan@dptechnics.com>
 *
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/gpio.h>

#include <asm/mach-ath79/ath79.h>
#include <asm/mach-ath79/ar71xx_regs.h>

#include "common.h"
#include "dev-eth.h"
#include "dev-gpio-buttons.h"
#include "dev-leds-gpio.h"
#include "dev-spi.h"
#include "dev-m25p80.h"
#include "dev-wmac.h"
#include "machtypes.h"
#include "dev-usb.h"

#define DPT_MODULE_GPIO_BTN_RESET	11					/* System reset button on breakout board */
#define DPT_MODULE_GPIO_LED_SYSTEM	27					/* Green system led on module board */
#define DPT_MODULE_EXT_SPI_CS		26					/* External SPI device chip select */

#define DPT_MODULE_KEYS_POLL_INTERVAL	20					/* 20 milliseconds poll interval */
#define DPT_MODULE_KEYS_DEBOUNCE_INTERVAL (3 * DPT_MODULE_KEYS_POLL_INTERVAL)	/* 3 checks must be pressed for keypress */

static const char *dpt_module_part_probes[] = {
	"tp-link",
	NULL,
};

static struct flash_platform_data dpt_module_flash_data = {
	.part_probes	= dpt_module_part_probes,
};

/* LED configuration */
static struct gpio_led dpt_module_leds_gpio[] __initdata = {
	{
		.name		= "dptmodule:green:system",
		.gpio		= DPT_MODULE_GPIO_LED_SYSTEM,
		.active_low	= 1,
	},
};

/* Key configuration */
static struct gpio_keys_button dpt_module_gpio_keys[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = DPT_MODULE_KEYS_DEBOUNCE_INTERVAL,
		.gpio		= DPT_MODULE_GPIO_BTN_RESET,
		.active_low	= 1,
	},
};

/* Hardware SPI chip select configuration */
static struct ath79_spi_controller_data ath79_spi1_data = {
	.cs_type = ATH79_SPI_CS_TYPE_GPIO,
	.cs_line = DPT_MODULE_EXT_SPI_CS,
};

/* HardwarSPI Board info */
static struct spi_board_info ath79_spi_info[] = {
	{
		.bus_num		= 0,
		.chip_select		= 1,
		.max_speed_hz		= 2500000,
		.modalias		= "spidev",
		.controller_data 	= &ath79_spi1_data,
	}
};

/* Board setup handler */
static void __init dpt_module_setup(void)
{
	u8 *mac = (u8 *) KSEG1ADDR(0x1f01fc00);
	u8 *ee = (u8 *) KSEG1ADDR(0x1fff1000);

	ath79_register_m25p80(&dpt_module_flash_data);

	ath79_gpio_function_disable(
		AR933X_GPIO_FUNC_ETH_SWITCH_LED0_EN |
                AR933X_GPIO_FUNC_ETH_SWITCH_LED1_EN |
                AR933X_GPIO_FUNC_ETH_SWITCH_LED2_EN |
                AR933X_GPIO_FUNC_ETH_SWITCH_LED3_EN |
                AR933X_GPIO_FUNC_ETH_SWITCH_LED4_EN);

	ath79_register_leds_gpio(-1, ARRAY_SIZE(dpt_module_leds_gpio), dpt_module_leds_gpio);

	ath79_register_gpio_keys_polled(-1, DPT_MODULE_KEYS_POLL_INTERVAL,
					ARRAY_SIZE(dpt_module_gpio_keys),
					dpt_module_gpio_keys);

	ath79_register_usb();

	ath79_init_mac(ath79_eth0_data.mac_addr, mac, 1);
	ath79_init_mac(ath79_eth1_data.mac_addr, mac, -1);

	ath79_register_mdio(0, 0x0);
	ath79_register_eth(1);
	ath79_register_eth(0);

	ath79_register_wmac(ee, mac);

	spi_register_board_info(ath79_spi_info, ARRAY_SIZE(ath79_spi_info));
}

MIPS_MACHINE(ATH79_MACH_DPT_MODULE, "DPT-MODULE", "DPT-Module V1.0", dpt_module_setup);
