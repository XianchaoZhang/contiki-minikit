#include "dev/models.h"
#include "dev/leds.h"

void
leds_arch_init(void)
{
	gpio_set_mode(LED_GPIO, GPIO_MODE_OUTPUT_2_MHZ,
      GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN);
}

unsigned char
leds_arch_get(void)
{
	if(gpio_get(LED_GPIO, LED_PIN)) {
		return LEDS_YELLOW;
  } else {
		return 0;
  }
}

void
leds_arch_set(unsigned char leds)
{
	if(leds & LEDS_YELLOW) {
    gpio_set(LED_GPIO, LED_PIN);
  } else {
    gpio_clear(LED_GPIO, LED_PIN);
  }
}
