#include <stdio.h>
#include <stdlib.h>

#include "board_setup.h"
#include "valid_play.h"
#include "board_struct.h"


void play_minesweeper(int rows, int cols, int mines, int seedVal){
    
    BOARD board; //initializes BOARD struct as board
    
    board.next_move = false; //initializes next_moves as false
    board.num_rows = rows;   //initializes num_rows as the number of rows the user entered through the command line
    board.num_cols = cols;   //initializes num_cols as the number of columns entered
    board.num_mines = mines; //initializes num_mines as the number of mines entered
    
    mine_layout(&board, seedVal); //sets up a board with all numbered tiles and correctly placed mines
    set_up(&board); //sets up a separate board with each tile concealed
    
    //While the game is not over...
    while(!game_over(board)){

        total_mines(board); //Function indicates the number of mines remaining
        
        display_board(board); //Function displays the board with concealed tiles in which the user begins revealing
        

        //While the next_move is not valid...
        do{
            get_play(board, &rows, &cols); //Asks user for a specified row and column
        
            get_action(&board, rows, cols); //Asks user for an action
            
        }while(!board.next_move);
    }
    
    //After the game is over...

    display_layout(board); //Displays the actual layout of the board, where all the tiles and mines are placed
    declare_winner(board); //Declares whether the user lost or won
    clean_up(&board);      //Cleans up the mallocated boards
}



void validArgs(int argc) {
    
    //If the number of arguments exceeds five print, this usage statement
    if(argc > 5){
        
        printf("Too many arguments. ");

        printf("Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])");
        
        exit(0); //closes program
    }
    
    //If the number of arguments is less then five, print this usage statement 
    if(argc < 5){
        
        printf("Not enough arguments. ");

        printf("Usage: ./mine_sweeper.out num_rows num_cols num_mines [seed])");
        
        exit(0); //closes program
    }
}



int main(int argc, char* argv[]) {
    
    int rows, cols, mines, seedVal; //variables declared to assign the four command line arguments
    
    validArgs(argc); //calls function to validate number of arguments
    
    rows = atoi(argv[1]); //assigns second argument into an integer representing the number of rows
    
    cols = atoi(argv[2]); //assigns third argument representing the number of columns
    
    mines = atoi(argv[3]); //assigns fourth argument representing the number of mines
    
    seedVal = atoi(argv[4]); //assigns fifth argument representing the seed value
    
    play_minesweeper(rows, cols, mines, seedVal); //Starts the game
    
    return 0;
}