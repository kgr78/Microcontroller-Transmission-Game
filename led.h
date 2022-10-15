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

void welcome_screen(void);
void init_screen(void);  
bool exit_welcome(void);  
int display_outcome(int8_t symbol); 
 

#endif