#ifndef LED_H
#define LED_H
//kahu
/**Says the title of the game when it starts*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "ir_uart.h"
#include "navswitch.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



void welcome_screen(void);
void init_screen(void);  
bool exit_welcome(void);  
void display_outcome(int8_t symbol); 
void display_winner(int8_t winner_int,int8_t loser_int);
void display_loser(int8_t loser_int, int8_t winner_int); 

#endif