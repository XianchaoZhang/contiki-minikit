#include <stdint.h>
#include <stdio.h>
#include <sys/process.h>
#include <sys/procinit.h>
#include <etimer.h>
#include <sys/autostart.h>
#include <clock.h>
#include <string.h>

#include <libopencm3/stm32/f1/rcc.h>
#include <libopencm3/stm32/f1/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/f1/nvic.h>
#include <errno.h>

#include "dev/models.h"
#include "dev/leds.h"
#include "net/tcpip.h"
#include "net/uip-ds6.h"

void clock_setup(void)
{
  rcc_clock_setup_in_hsi_out_48mhz();

  /* Enable clocks for GPIO port A, B and USART1. */
  rcc_peripheral_enable_clock(&RCC_APB2ENR, 
      RCC_APB2ENR_IOPAEN |
      RCC_APB2ENR_IOPCEN |
      RCC_APB2ENR_AFIOEN );
}

void
uip_log(char *msg)
{
	printf("%s\n", msg);
}

unsigned int idle_count = 0;

int
main()
{
	clock_setup();

	clock_init();
	leds_arch_init();
	process_init();
	process_start(&etimer_process, NULL);

	autostart_start(autostart_processes);

	leds_arch_set(LEDS_YELLOW);

	while(1) {
		do {
		} while(process_run() > 0);
		idle_count++;
		leds_arch_set(LEDS_GREEN);
	}
	return 0;
}

