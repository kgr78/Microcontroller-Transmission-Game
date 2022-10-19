/** @file player_choice.c 
 * @author K. G. Griffin
 * @date  12 Oct, 2022
 * @brief displays titles, values, scores / outcomes
*/

#ifndef LED_H
#define LED_H


#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"
#include "navswitch.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/**Says the title of the game when it starts*/
void welcome_screen(void);
/*Initialises the led board to display*/
void init_screen(void);  
/*displays the outcome of the winner or the loser or each round*/
void display_outcome(int8_t symbol); 
/*displays the winner screen and final score*/
void display_winner(int8_t winner_int,int8_t loser_int);
/*displays the loser screen and final score*/
void display_loser(int8_t loser_int, int8_t winner_int); 

#endif