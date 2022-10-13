#include "system.h"
#include "pio.h"
#include "pacer.h"


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


static const uint8_t bitmap_rock[] =
{
    0x00, 
    0x0C, 
    0x12, 
    0x12, 
    0x0C
    // rock
};
static const uint8_t bitmap_paper[] =
{    
    0x00,
    0x1E,
    0x1E,
    0x1E,
    0x00
    // paper
};
static const uint8_t bitmap_scissors[] =
{
    0x71,
    0x72,
    0x04,
    0x72,
    0x71
    // scissors
};
static const uint8_t bitmap_loss[] =
{
    0x22,
    0x14,
    0x08,
    0x14,
    0x22
    // X
};
static const uint8_t bitmap_win[] =
{
    0x10,
    0x20,
    0x10,
    0x08,
    0x04,
    // tick
};
static const uint8_t bitmap_draw[] =
{
    0x00,
    0x08,
    0x08,
    0x08,
    0x00
    // dash
};



static void display_column (uint8_t row_pattern, uint8_t current_column)
{

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

    /* TODO */
}


int main (int8_t symbol)
{
    uint8_t current_column = 0;
  
    system_init ();
    pacer_init (500);
    for (int16_t i = 0; i < LEDMAT_ROWS_NUM; i++) {
        pio_config_set (rows[i], PIO_OUTPUT_HIGH);
    }
    for (int16_t i = 0; i < LEDMAT_ROWS_NUM; i++) {
        pio_config_set (cols[i], PIO_OUTPUT_HIGH);
    }
    /* TODO: Initialise LED matrix pins.  */
    

    while (1)
    {
        if (symbol == 1) {
            pacer_wait ();
            display_column (bitmap_paper[current_column], current_column);
            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }                       
        }
        if (symbol == 2) {
            pacer_wait ();
            display_column (bitmap_scissors[current_column], current_column);
            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }    
        }
        if (symbol == 3) {
            pacer_wait ();
            display_column (bitmap_scissors[current_column], current_column);
            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }    
        }
        if (symbol == 4) {
            pacer_wait ();
            display_column (bitmap_rock[current_column], current_column);
            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }    
        }
        if (symbol == 5) {
            pacer_wait ();
            display_column (bitmap_win[current_column], current_column);
            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }    
        }
        if (symbol == 6) {
            pacer_wait ();
            display_column (bitmap_loss[current_column], current_column);
            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }    
        }
        if (symbol == 7) {
            pacer_wait ();
            display_column (bitmap_draw[current_column], current_column);
            current_column++;
            if (current_column > (LEDMAT_COLS_NUM - 1))
            {
                current_column = 0;
            }    
        }
    }
}
