#include "decide_winner.h"
#include "system.h"
#include "led.h"

int result(char recieved, char chosen) {
    int player1 = 1; 
    int winner;
    int player2 = 2; 
    int draw = 3; 
    if (recieved == chosen) {
        winner = draw; 
        display_outcome(winner);  
    } else if (recieved == 'R' && chosen == 'P') {
        winner = player1; 
        display_outcome(winner); 
    } else if (recieved == 'R' && chosen == 'S') {
        winner = player2;
        display_outcome(winner);  
    } else if (recieved == 'P' && chosen == 'R') {
        winner = player2;
        display_outcome(winner);  
    } else if (recieved == 'P' && chosen == 'S') {
        winner = player1; 
        display_outcome(winner); 
    } else if (recieved == 'S' && chosen == 'R') {
        winner = player1;
        display_outcome(winner);  
    } else {
        winner = player2; 
        display_outcome(winner); 
    }
    return winner; 
}