#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/ethernet.h"
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "utils/lwiplib.h"

#include "config.h"
#include "c2e_eth.h"

uint32_t ETH_init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);                          // Enable the Ethernet Controller.
    SysCtlPeripheralReset(SYSCTL_PERIPH_ETH);                           // Reset the Ethernet Controller.

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                        // Enable Port F for Ethernet LEDs.
    GPIOPinTypeEthernetLED(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);   // LED0-Bit 3-Output and LED1-Bit 2-Output

    SysTickPeriodSet(SysCtlClockGet() / SYSTICKHZ);                     // Configure SysTick for a periodic interrupt. Used by lwIP - NB the choice of this seems to be important e.g. lwIPgetLocalIPAddr returns wrong value 
    SysTickEnable();                                                    // TODO: investigate why SYSTICKNS doesn't seem to work
    SysTickIntEnable();
    return ST_ETHINIT;
}


void get_mac_address(unsigned char *mac_address)						// Configure the hardware MAC address for Ethernet Controller filtering of incoming packets. 
{																		// MAC address is stored in the non-volatile USER0 and USER1 registers
	uint32_t user0, user1;                                         // variables to retrieve MAC address from flash
	FlashUserGet(&user0, &user1);
    if((user0 == 0xffffffff) || (user1 == 0xffffffff))
    {
        // We should never get here.  This is an error if the MAC address has not been programmed into the device.  Exit the program.
        //RIT128x96x4StringDraw("MAC Address", 0, 16, 15);
        //RIT128x96x4StringDraw("Not Programmed!", 0, 24, 15);
        while(1);
    }
    // Convert the 24/24 split MAC address from NV ram into a 32/16 split MAC address needed to program the hardware registers, 
    mac_address[0] = ((user0 >>  0) & 0xff);
    mac_address[1] = ((user0 >>  8) & 0xff);
    mac_address[2] = ((user0 >> 16) & 0xff);
    mac_address[3] = ((user1 >>  0) & 0xff);
    mac_address[4] = ((user1 >>  8) & 0xff);
    mac_address[5] = ((user1 >> 16) & 0xff);
}

