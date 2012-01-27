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
#include <libopencm3/stm32/nvic.h>
#include <errno.h>

#include "dev/models.h"
#include "dev/slip.h"
#include "net/tcpip.h"
#include "net/uip-ds6.h"

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
	nvic_enable_irq(NVIC_USART1_IRQ);

	gpio_set_mode(USART_GPIO, GPIO_MODE_OUTPUT_50_MHZ,
		      GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, USART_TX_PIN);

	gpio_set_mode(USART_GPIO, GPIO_MODE_INPUT,
		      GPIO_CNF_INPUT_FLOAT, USART_RX_PIN);

	/* Setup UART parameters. */
	usart_set_baudrate(USART1, 19200);
	usart_set_databits(USART1, 8);
	usart_set_stopbits(USART1, USART_STOPBITS_1);
	usart_set_parity(USART1, USART_PARITY_NONE);
	usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);
	usart_set_mode(USART1, USART_MODE_TX_RX);

	/* Enable USART1 Receive interrupt. */
	USART_CR1(USART1) |= USART_CR1_RXNEIE;

	/* Finally enable the USART. */
	usart_enable(USART1);
}

void slip_setup(void)
{
  uip_lladdr_t my_lladdr = {{SLIP_LINKLEVEL_ADDR}};
  memcpy(&uip_lladdr, &my_lladdr, sizeof(uip_lladdr));

  tcpip_set_outputfunc(slip_send);

  process_start(&tcpip_process, "TCP/IP stack");
  process_start(&slip_process, "SLIP");

  uip_ipaddr_t ipaddr;
  SLIP_REMOTE_IP;
  uip_ds6_nbr_add(&ipaddr, &my_lladdr, 0, NBR_REACHABLE);
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
	usart_setup();

  printf("Initialising\n");

  clock_init();
  process_init();
  process_start(&etimer_process, NULL);

  if(WITH_SLIP) {
    slip_setup();
  }

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

