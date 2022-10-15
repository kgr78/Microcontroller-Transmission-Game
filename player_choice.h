#ifndef PLAYER_CHOICE_H
#define PLAYER_CHOICE_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

void display_character (char character); 
char change_character(int8_t count); 
void choose_character(void); 


#endif