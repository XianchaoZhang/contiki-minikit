#include <libopencm3/stm32/f1/gpio.h>
#include <libopencm3/stm32/f1/rcc.h>

#include "dev/leds.h"

void
leds_arch_init(void)
{
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPBEN);

	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ,
      GPIO_CNF_OUTPUT_PUSHPULL, GPIO2);
}

unsigned char
leds_arch_get(void)
{
	if(gpio_get(GPIOB, GPIO2)) {
		return LEDS_YELLOW;
  } else {
		return 0;
  }
}

void
leds_arch_set(unsigned char leds)
{
	if(leds & LEDS_YELLOW) {
    gpio_set(GPIOB, GPIO2);
  } else {
    gpio_clear(GPIOB, GPIO2);
  }
}
