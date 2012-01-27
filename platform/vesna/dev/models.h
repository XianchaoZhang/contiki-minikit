#ifndef __MODELS_H__
#define __MODELS_H__

#include <libopencm3/stm32/f1/gpio.h>
#include <libopencm3/stm32/f1/rcc.h>

/* default setup */
#define VESNA_SNC

/* pin assignments */
#define LED_GPIO    GPIOB
#define LED_PIN     GPIO2

#define USART_GPIO     GPIOA
#define USART_TX_PIN   GPIO9
#define USART_RX_PIN   GPIO10

/* stand-alone VESNA sensor node core, possibly connected via SLIP */
#ifdef VESNA_SNC
# define WITH_SLIP  1
#endif

#endif
