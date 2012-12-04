#ifndef __C2E_CAN_ETHERNET_H
#define __C2E_CAN_ETHERNET_H
#include <stdint.h>

static uint32_t display_ip_address(void);							// display an lwIP address
static uint32_t fsm_error(void);																			// catch all state machine function
static uint32_t INT_init(void);
static uint32_t LWIP_init(void);
static uint32_t NETIF_init(void);
static uint32_t IPaddr_init(void);
void PENDSV_handler(void);																			// PendSV interrup handler - causes UDP packets with embedded CAN frames to be sent. Triggered in SW when RingBuffer reaches a threshold.

#endif
