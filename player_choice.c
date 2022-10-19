/** @file player_choice.c 
 * @author K. G. Griffin
 * @date  15 Oct, 2022
 * @brief getting player choice, sending and recieving it as well as doing final winner
*/


#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "player_choice.h"
#include "led.h" 
#include "decide_winner.h"
#include <stdbool.h>

/* Sets the pacer rate and the message speed*/
#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    /*Makes char array and adds the current character
    \0 added to show end of text
    displays the char array with tinygl_text*/
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

char change_character(int8_t count) {
    /*initialises character and returns a character depending on input value*/
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
    /*initialises values,bools,screen,navswitch and displaying first character of 'P' */
    int8_t count = 0; 
    char character = change_character(count);
    char recieved; 
    char chosen = 0;
    int8_t player1 = 0, player2 = 0, yourself =1, opponent =2, save_player1 =0, save_player2 =0; 
    init_screen(); 
    ir_uart_init ();
    navswitch_init ();
    pacer_init (PACER_RATE);

    /*loops until a player one or two has won 3 games*/
    while (player1 < 3 && player2 < 3) 
    {
        /*updating navswitch and waiting for next pacer tick*/
        pacer_wait ();
        
        navswitch_update ();

        /*checking if the navswitch is moved north, adding to the count if its 0 or 1
        Then changing the new character*/
        if (navswitch_push_event_p (NAVSWITCH_NORTH))
            if (count >= 0 && count <= 1) {
                count++;
                character = change_character(count); 
            }  
        /*checking if the navswitch is moved south, minusing to the count if its 1 or 2 
        Then changing the new character*/  
        if (navswitch_push_event_p (NAVSWITCH_SOUTH))
            if (count > 0 && count <= 2) {
                count--;
                character = change_character(count); 
            }
        /*checking if navswitch is pushed down. 
        Setting the chosen character with ascii in value 
        sending out the character*/
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
            chosen = character;
        }
        /*displaying the current characters*/
        display_character (character);  
        /*checks that something has been sent
        Then gets that value*/
        if (ir_uart_read_ready_p()) {
            recieved = ir_uart_getc();
            /*checks see if that value sent is a valid value and if the player has sent anything*/
            if ((recieved == 'R' || recieved == 'P' || recieved == 'S') && (chosen != 0)) {
                /*sends again to make sure that it was sent
                Displays the winner and decides who wins
                incimenting the winner depending on the value returned*/
                ir_uart_putc(chosen);
                int winner = result(recieved, chosen); 
                chosen = 0; 
                if (winner == yourself) {
                    player1++;
                } else if (winner == opponent) {
                    player2++; 
                }
            }
        }
        /*updating the display*/
        tinygl_update ();
         
    }
    /*saving the score for final outcome
    Reseting all values for the next game*/
    save_player1 = player1;
    save_player2 = player2;
    player1 = 0; 
    player2 = 0; 
    count = 0; 
    chosen = 0; 
    /*Displaying the final outcome*/
    final_outcome(save_player1,save_player2); 
}

void final_outcome(int8_t player1, int8_t player2) {
    /*checks if you won and displays winning screen 
    else the opponent won and displays loser screen*/
    if (player1>player2) {
        display_winner(player1,player2); 
    } else {
        display_loser(player1,player2); 
    }
}