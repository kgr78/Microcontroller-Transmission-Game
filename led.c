#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"

/* Sets the pacer rate and the message speed*/
#define PACER_RATE 500
#define MESSAGE_RATE 10


void welcome_screen(void) {
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);

    pacer_init (PACER_RATE);
    tinygl_text("Paper Scissors Rock"); 
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    while(1)
    {
        pacer_wait();
        /* Calls the tinygl update function. */
        tinygl_update (); 
    }
}