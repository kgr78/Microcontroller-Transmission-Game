#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "player_choice.h"
#include "led.h" 
#include "decide_winner.h"
#include <stdbool.h>


#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

char change_character(int8_t count) {
    char character; 
    if (count == 0) {
        character = 'P';
    } else if (count == 1) {
        character = 'S';
    } else {
        character = 'R'; 
    }
    return character; 
}
void choose_character(void) {
    int8_t count = 0; 
    char character = change_character(count);
    char recieved; 
    char chosen = 0;
    int8_t player1 = 0, player2 = 0; 
    init_screen(); 
    ir_uart_init ();
    navswitch_init ();
    pacer_init (PACER_RATE);


    while (player1 < 3 && player2 < 3) 
    {
        pacer_wait ();
        
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH))
            if (count >= 0 && count <= 1) {
                count++;
                character = change_character(count); 
            }    
        if (navswitch_push_event_p (NAVSWITCH_SOUTH))
            if (count > 0 && count <= 2) {
                count--;
                character = change_character(count); 
            }
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
            chosen = character;
        }
        display_character (character);  
        if (ir_uart_read_ready_p()) {
            recieved = ir_uart_getc();
            if ((recieved == 'R' || recieved == 'P' || recieved == 'S') && (chosen != 0)) {
                ir_uart_putc(chosen);
                int winner = result(recieved, chosen); 
                chosen = 0; 
                if (winner == 1) {
                    player1++;
                } else if (winner == 2) {
                    player2++; 
                }
            }
        }
        tinygl_update ();
         
    }
    int8_t player21 = player1;
    int8_t player22 = player2;
    player1 = 0; 
    player2 = 0; 
    count = 0; 
    chosen = 0; 
    final_outcome(player21,player22); 
}

void final_outcome(int8_t player1, int8_t player2) {
    if (player1>player2) {
        display_winner(player1,player2); 
    } else {
        display_loser(player1,player2); 
    }
}