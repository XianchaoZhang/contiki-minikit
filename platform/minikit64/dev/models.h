#ifndef __MODELS_H__
#define __MODELS_H__

#include <libopencm3/stm32/f1/gpio.h>
#include <libopencm3/stm32/f1/rcc.h>

/* default setup */
#define MINIKIT

/* pin assignments */
#define LED_GPIO    GPIOB
#define LED_PIN     GPIO0

#define USART_GPIO     GPIOA
#define USART_TX_PIN   GPIO9
#define USART_RX_PIN   GPIO10

#ifdef MINIKIT
# define WITH_SLIP  1
#endif

#endif
