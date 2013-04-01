#ifndef __CONTIKI_CONF_H__CDBB4VIH3I__
#define __CONTIKI_CONF_H__CDBB4VIH3I__

#include <stdint.h>

#define CCIF
#define CLIF
#define WITH_UIP 1
#define WITH_ASCII 1

#define CLOCK_CONF_SECOND 100
typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef int8_t s8_t;
typedef int16_t s16_t;
typedef int32_t s32_t;

typedef unsigned int clock_time_t;
typedef unsigned int uip_stats_t;

/* this is used to define the local link-local IPv6 address */
#define SLIP_LINKLEVEL_ADDR 0x00,0x00,0x00,0x00,0x00,0x02

/* Neighbor solicitation doesn't work through SLIP, so we need
 * to know the IP of the remote computer. */
#define SLIP_REMOTE_IP uip_ip6addr(&ipaddr,0xfe80,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0001)

#endif /* __CONTIKI_CONF_H__CDBB4VIH3I__ */
