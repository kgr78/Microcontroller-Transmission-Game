/** @file game.c
 * @author K. G. Griffin
 * @date  12 Oct, 2022
 * @brief sets up the game
*/


#include "system.h"
#include "led.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "player_choice.h"
#include <stdbool.h>



int main (void)
{
    /*loops through game and initialises
    constant loops so that game will not end*/
    while (1)
    {
        system_init();
        ir_uart_init(); 
        welcome_screen(); 
        choose_character(); 
    }
}
