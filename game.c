#include "system.h"
#include "led.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "led_symbols.h"
#include "player_choice.h"
//kahu


int main (void)
{
    system_init();
    ir_uart_init();
    choose_character();
    // system_init ();
    // ir_uart_init ();
    // int8_t sent = 0;
    // int8_t received = 0;
    // welcome_screen();
    // while (sent != 1 && received != 1)
    // {
    //     if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
    //         ir_uart_putc ('?');
    //         sent = 1;
    //     }
    //     if (ir_uart_read_ready_p ())
    //     {
    //         if (ir_uart_getc () == "?") {
    //             received = 1;
    //         }
    //     }
    // }
    
}
