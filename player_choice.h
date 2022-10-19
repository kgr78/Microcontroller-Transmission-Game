/** @file player_choice.c 
 * @author K. G. Griffin
 * @date  15 Oct, 2022
 * @brief player choice, sending and recieving and final outcome 
*/



#ifndef PLAYER_CHOICE_H
#define PLAYER_CHOICE_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

/*adds character to char array and dispalys it using tinygl*/
void display_character (char character); 
/*changes character and returns it based on given count*/
char change_character(int8_t count); 
/*switches between characters with display_character, change_character
sends and recieves chosen values
while saving score for each player*/
void choose_character(void); 
/*displays final outcome but recieving the players scores*/
void final_outcome(int8_t player1, int8_t player2); 


#endif