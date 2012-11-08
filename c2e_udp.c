#include "utils/lwiplib.h"

#include "utils/ustdlib.h"
#include "drivers/rit128x96x4.h"
#include "c2e_udp.h"

static char print_buf[64];

void UDP_configure(void)
{
	void *pcb;
    pcb = udp_new();
    udp_recv(pcb, UDP_receive, NULL);										// set callback for incoming UDP data
    udp_bind(pcb, IP_ADDR_ANY, 23);
}

void UDP_send(void)
{
    void *pcb;
    unsigned char *pucData;
    struct pbuf *p;

    pcb = udp_new();
    udp_recv(pcb, UDP_receive, NULL);                                       // set callback for incoming UDP data
    udp_bind(pcb, IP_ADDR_ANY, 23);

    
    p = pbuf_alloc(PBUF_TRANSPORT, 4, PBUF_RAM);            // Allocate a pbuf for this data packet.
    if(!p)
    {
        RIT128x96x4StringDraw("Here", 5, 20, 15);
        return;
    }

    
    pucData = (unsigned char *)p->payload;                  // Get a pointer to the data packet.

    //
    // Fill in the packet header.
    //
    pucData[0] = 1;
    pucData[1] = 2;
    pucData[2] = 3;
    pucData[3] = 4;

    err_t status;
    RIT128x96x4StringDraw("Before send", 10, 20, 15);
    status = udp_sendto(pcb, p, IP_ADDR_BROADCAST, 23);
    RIT128x96x4StringDraw("After send", 10, 30, 15);
    usprintf(print_buf, "status = %u  ", status);
    RIT128x96x4StringDraw(print_buf, 10, 40, 15);
    
    //udp_send(psTFTP->pPCB, p);      // Send the data packet.
    pbuf_free(p);       // Free the pbuf.
}

//*****************************************************************************
//
// This function is called by the lwIP TCP/IP stack when it receives a UDP
// packet from the discovery port.  It produces the response packet, which is
// sent back to the querying client.
//
//*****************************************************************************
void UDP_receive(void *arg, struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    //unsigned char *pucData;
    //unsigned long ulIdx;

/*
    //
    // Validate the contents of the datagram.
    //
    pucData = p->payload;
    if((p->len != 4) || (pucData[0] != TAG_CMD) || (pucData[1] != 4) ||
       (pucData[2] != CMD_DISCOVER_TARGET) ||
       (pucData[3] != ((0 - TAG_CMD - 4 - CMD_DISCOVER_TARGET) & 0xff)))
    {
        pbuf_free(p);
        return;
    }
*/
    //
    // The incoming pbuf is no longer needed, so free it.
    //
    pbuf_free(p);

    /*
    //
    // Allocate a new pbuf for sending the response.
    //
    p = pbuf_alloc(PBUF_TRANSPORT, sizeof(g_pucLocatorData), PBUF_RAM);
    if(p == NULL)
    {
        return;
    }

    //
    // Calcuate and fill in the checksum on the response packet.
    //
    for(ulIdx = 0, g_pucLocatorData[sizeof(g_pucLocatorData) - 1] = 0;
        ulIdx < (sizeof(g_pucLocatorData) - 1); ulIdx++)
    {
        g_pucLocatorData[sizeof(g_pucLocatorData) - 1] -=
            g_pucLocatorData[ulIdx];
    }

    //
    // Copy the response packet data into the pbuf.
    //
    pucData = p->payload;
    for(ulIdx = 0; ulIdx < sizeof(g_pucLocatorData); ulIdx++)
    {
        pucData[ulIdx] = g_pucLocatorData[ulIdx];
    }
    */

    //
    // Send the response.
    //
    //udp_sendto(pcb, p, addr, port);

    //
    // Free the pbuf.
    //
    //pbuf_free(p);
}