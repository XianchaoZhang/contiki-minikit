#include <sys/etimer.h>
#include <libopencm3/stm32/systick.h>
#include <libopencm3/stm32/nvic.h>
#include <libopencm3/stm32/f1/scb.h>

static volatile clock_time_t current_clock = 0;
static volatile unsigned long current_seconds = 0;
static unsigned int second_countdown = CLOCK_SECOND;

void
sys_tick_handler(void) __attribute__ ((interrupt));

void
sys_tick_handler(void)
{
  //(void)SysTick->CTRL;
  SCB_ICSR = SCB_ICSR_PENDSTCLR;
  current_clock++;
  if(etimer_pending() && etimer_next_expiration_time() <= current_clock) {
    etimer_request_poll();
  }
  if (--second_countdown == 0) {
    current_seconds++;
    second_countdown = CLOCK_SECOND;
  }
}


void
clock_init()
{
  nvic_set_priority(NVIC_SYSTICK_IRQ, 8);
  systick_set_reload(MCK/8/CLOCK_SECOND);
  systick_counter_enable();
  systick_interrupt_enable();
}

clock_time_t
clock_time(void)
{
  return current_clock;
}

unsigned long
clock_seconds(void)
{
  return current_seconds;
}

/* Undocumented function, delaying for a platform-dependent time? */
void
clock_delay(unsigned int delay)
{
  for(; delay > 0; delay--) {
    asm("nop");
  }
}
