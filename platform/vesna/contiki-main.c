#include <stdint.h>
#include <stdio.h>
#include <sys/process.h>
#include <sys/procinit.h>
#include <etimer.h>
#include <sys/autostart.h>
#include <clock.h>

#include <libopencm3/stm32/f1/rcc.h>
#include <libopencm3/stm32/f1/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/nvic.h>
#include <errno.h>

#include "dev/models.h"

void clock_setup(void)
{
  rcc_clock_setup_in_hsi_out_48mhz();

  /* Enable clocks for GPIO port A, B and USART1. */
  rcc_peripheral_enable_clock(&RCC_APB2ENR, 
      RCC_APB2ENR_IOPAEN |
      RCC_APB2ENR_IOPBEN |
      RCC_APB2ENR_AFIOEN | 
      RCC_APB2ENR_USART1EN);
}

void usart_setup(void)
{
	gpio_set_mode(USART_GPIO, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, USART_PIN);

	/* Setup UART parameters. */
	usart_set_baudrate(USART1, 19200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART1, USART_MODE_TX);

	/* Finally enable the USART. */
	usart_enable(USART1);
}

int _write(int file, char *ptr, int len)
{
	int i;

	if (file == 1) {
		for (i = 0; i < len; i++)
			usart_send_blocking(USART1, ptr[i]);
		return i;
	}

	errno = EIO;
	return -1;
}

unsigned int idle_count = 0;

int
main()
{
	clock_setup();
	usart_setup();

  //dbg_setup_uart();
  printf("Initialising\n");
  
  clock_init();
  process_init();
  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);
  printf("Processes running\n");
  while(1) {
    do {
    } while(process_run() > 0);
    idle_count++;
    /* Idle! */
    /* Stop processor clock */
    /* asm("wfi"::); */ 
  }
  return 0;
}

