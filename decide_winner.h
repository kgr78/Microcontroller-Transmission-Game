/** @file player_choice.c 
 * @author K. G. Griffin
 * @date  15 Oct, 2022
 * @brief decides the winner of rounds
*/


#ifndef DECIDE_WINNER_H
#define DECIDE_WINNER_H

#include "decide_winner.h"
#include "system.h"
#include "led.h"

/*decides the winner based on chosen value and recieved values*/
int result(char recieved, char chosen); 


#endif