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

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

//kahu
void init_screen(void) {
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
}

void welcome_screen(void) {
    init_screen(); 
    display_init();
    tinygl_text("Paper Scissors Rock"); 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init (PACER_RATE);
    bool pushed = false;
    while (!pushed) {
        pacer_wait();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;
        }
        tinygl_update ();
    }
}

static void display_column (uint8_t row_pattern, uint8_t current_column) {
    static uint8_t old_column;
    pio_output_high (cols[old_column]);
    old_column = current_column;

    for (int16_t i = 0; i < LEDMAT_ROWS_NUM; i++) {
        uint8_t current_row = i;
        if ((row_pattern >> current_row) & 1) {
            pio_output_low (rows[current_row]);
        } else {
            pio_output_high (rows[current_row]);
        }
    }
    pio_output_low (cols[current_column]);
}

void display_outcome(int8_t symbol) {
    tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
    if (symbol == 1) {
        init_screen(); 
        tinygl_text("W");
        pacer_init (PACER_RATE); 
        bool pushed = false;
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
    tinygl_clear();
    init_screen(); 
    display_init();
    tinygl_text("Winner!"); 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init (PACER_RATE);
    bool pushed = false;
    while (!pushed) {
        pacer_wait();
        navswitch_update();
        /* Calls the tinygl update function. */
        
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;
        }
        tinygl_update (); 
        
    }

    pushed = false; 
    char end_score[100] = "Score:    ";   
    winner_int = '0' + winner_int;
    loser_int = '0' + loser_int; 
    end_score[6] = winner_int;  
    end_score[7] = '-'; 
    end_score[8] = loser_int; 
    tinygl_text(end_score); 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
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

void display_loser(int8_t loser_int, int8_t winner_int) {
    tinygl_clear();
    init_screen(); 
    display_init();
    tinygl_text("Loser :("); 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    pacer_init (PACER_RATE);
    bool pushed = false;
    while (!pushed) {
        pacer_wait();
        navswitch_update();
        /* Calls the tinygl update function. */
        
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            pushed = true;

        }
        
        tinygl_update (); 
    }

    pushed = false; 
    char end_score[100] = "Score:    ";   
    winner_int = '0' + winner_int;
    loser_int = '0' + loser_int; 
    end_score[6] = winner_int;  
    end_score[7] = '-'; 
    end_score[8] = loser_int; 
    tinygl_text(end_score); 
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
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

