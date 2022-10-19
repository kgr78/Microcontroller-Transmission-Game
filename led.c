/** @file player_choice.c 
 * @author K. G. Griffin
 * @date  12 Oct, 2022
 * @brief displays titles, values, scores / outcomes
*/

#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "led.h"
#include "ir_uart.h"
#include "navswitch.h"
#include "pio.h"
#include <stdbool.h>
#include "player_choice.h"

/* Sets the pacer rate and the message speed*/
#define PACER_RATE 500
#define MESSAGE_RATE 10


void init_screen(void) {
    /*sets pacer rate, message speed and font*/
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
}

void welcome_screen(void) {
    init_screen(); 
    display_init();
    bool pushed = false;
    tinygl_text("Paper Scissors Rock");
    /*setting the text to scroll across the screen*/ 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init (PACER_RATE);
    /*Waiting for pushed to be true and exit the title loop*/
    while (!pushed) {
        /*updating navswitch and display each time it loops*/
        pacer_wait();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;
        }
        tinygl_update ();
    }
}


void display_outcome(int8_t symbol) {
    /*setting the mode to step*/
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    /*checking what kind of symbol is neede. 
    Dispalying the a W, L, T depeing on if they won, lost, tie that round. 
    Must push navswitch to move onto next game*/
    if (symbol == 1) {
        init_screen(); 
        tinygl_text("W");
        pacer_init (PACER_RATE); 
        bool pushed = false;
        /*updating navswitch and display each time it loops*/
        while (!pushed)
        {
            pacer_wait();
            navswitch_update ();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                pushed = true;
            }

            tinygl_update (); 
        } 
    }
    if (symbol == 2) {
        init_screen(); 
        tinygl_text("L");
        pacer_init (PACER_RATE); 
        bool pushed = false;
        /*updating navswitch and display each time it loops*/
        while (!pushed)
        {
            pacer_wait();
            navswitch_update ();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                pushed = true;
            }
            tinygl_update (); 
        } 
    }
    if (symbol == 3) {
        init_screen(); 
        tinygl_text("T");
        pacer_init (PACER_RATE); 
        bool pushed = false;
        /*updating navswitch and display each time it loops*/
        while (!pushed)
        {
            pacer_wait();
            navswitch_update ();
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                pushed = true;
            }
            
            tinygl_update (); 
        } 
    }
}

void display_winner(int8_t winner_int,int8_t loser_int) {
    /*Setting up initialisation, scroling and bool values*/
    tinygl_clear();
    init_screen(); 
    display_init();
    tinygl_text("Winner!"); 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init (PACER_RATE);
    bool pushed = false;
    /*displaying Winner unitl pushed is true*/
    while (!pushed) {
        pacer_wait();
        navswitch_update();
        
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;
        }
        tinygl_update (); 
        
    }
    /*setting pushed back to false for next while loop. 
    Macking the score an ascii value and adding it to char array to be displayed. 
    dispalying score until navswitch is pushed*/
    pushed = false; 
    char end_score[100] = "Score:    ";   
    winner_int = '0' + winner_int;
    loser_int = '0' + loser_int; 
    end_score[6] = winner_int;  
    end_score[7] = '-'; 
    end_score[8] = loser_int; 
    tinygl_text(end_score); 
    pacer_init (PACER_RATE);
    /*updating navswitch and display each time it loops*/
    while (!pushed) {
        pacer_wait();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;
        }
        tinygl_update (); 
        
    }
} 

void display_loser(int8_t loser_int, int8_t winner_int) {
    /*Setting up initialisation, scroling and bool values*/
    tinygl_clear();
    init_screen(); 
    display_init();
    tinygl_text("Loser :("); 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init (PACER_RATE);
    bool pushed = false;
    /*displaying Winner unitl pushed is true*/
    /*updating navswitch and display each time it loops*/
    while (!pushed) {
        pacer_wait();
        navswitch_update();
        
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;

        }
        
        tinygl_update (); 
    }
    /*setting pushed back to false for next while loop. 
    Macking the score an ascii value and adding it to char array to be displayed. 
    dispalying score until navswitch is pushed*/
    pushed = false; 
    char end_score[100] = "Score:    ";   
    winner_int = '0' + winner_int;
    loser_int = '0' + loser_int; 
    end_score[6] = winner_int;  
    end_score[7] = '-'; 
    end_score[8] = loser_int; 
    tinygl_text(end_score); 
    /*updating navswitch and display each time it loops*/
    pacer_init (PACER_RATE);
    while (!pushed) {
            pacer_wait();
            navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;
        }
        
        tinygl_update (); 
    }
}

