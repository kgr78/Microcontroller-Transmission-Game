#include "system.h"
#include "led.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "player_choice.h"
#include <stdbool.h>
//kahu


int main (void)
{
    system_init();
    ir_uart_init();
    welcome_screen();
    choose_character();

    
}
