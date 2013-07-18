/**
 * \file
 *         A very simple Contiki application showing how Contiki programs look
 * \author
 *         Xianchao Zhang <zhangxianchao@gmail.com>
 */

#include "contiki.h"
#include "dev/leds.h"

/*---------------------------------------------------------------------------*/
PROCESS(blink_flash_process, "Blink flash process");
AUTOSTART_PROCESSES(&blink_flash_process);
static process_event_t event_data_ready;

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(blink_flash_process, ev, data)
{
  PROCESS_BEGIN();
  static struct etimer timer;

  etimer_set(&timer, CLOCK_CONF_SECOND);

  event_data_ready = process_alloc_event();

  while (1)
  {
    PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

    leds_arch_set(LEDS_YELLOW);

    etimer_reset(&timer);
  }
  
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
