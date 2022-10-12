#include "system.h"
#include "led.h"
#include "navswitch.h"




int main (void)
{
    system_init ();
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc (1);
    }
    while (1)
    { 
        
    }

}
