#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "valid_play.h"
#include "board_setup.h"
#include "board_struct.h"


bool game_over(BOARD board){
    
    //To indicate the game is over, return true or false if the user has either won or lost
    return game_lost(board) || game_won(board);
    
}



bool game_lost(BOARD board){

    int i, j; //variable declared to represent number of rows, cols
    

    //To indiciate if the user lost, search through the whole bored to see if a mine was set off
    for(i = 0; i < board.num_rows; ++i){ //searches through each row
        for(j = 0; j < board.num_cols; ++j){ //searches through each column
            
            if(board.board_set[i][j] == '*'){

                return true; //If tile represents a mine, the user lost
            }
            
        }
    }
    
    
    
    return false; //otherwise the user hasn't lost and the game continues
}



bool game_won(BOARD board){
    
    int i, j;
    int count = 0; //variable declared to count the number of marks placed on the board
    

    //To indicate that the user won, search through the board to see if everything has been revealed and the correct amount of marks have been placed
    for(i = 0; i < board.num_rows; ++i){
        for(j = 0; j < board.num_cols; ++j){
            
            //If the tile is concealed or questioned, then the game hasn't been won
            if(board.board_set[i][j] == '#' || board.board_set[i][j] == '?'){

                return false;
            }
            
            //If a mark has been placed, add one to the count
            else if(board.board_set[i][j] == '!'){

                count = count + 1;
            }
        }
    }
    
    
    //If the correct number of marks have been place on top of all the mines and everything has been revealed, then the user has won 
    if(board.num_mines == count){

        return true;
    }
    

    return false; //Otherwise the user hasn't won and the game continues
}



void declare_winner(BOARD board){
    
    //If the user lost executes, losing statement
    if(game_lost(board)){
        
        printf("You Lost :(");

        exit(0); //ends program
    }
    
    //If the user has won, executes winning statement
    else if(game_won(board)){

        printf("You Won!!");

        exit(0); //ends program
    }
}



/* Function reads user's input of specified row and column */

void reveal_tiles(BOARD* board, int rows, int cols){
    
    //If the function searches out of bounds, returns with no result
    if(rows < 0 || rows >= board->num_rows || cols < 0 || cols >= board->num_cols){
        
        return;
    }
    

    //If the function encounters a mark or a question, the function does not reveal it
    else if(board->board_set[rows][cols] == '!' || board->board_set[rows][cols] == '?'){
        
        return;
    }
    
    
    //If a tile specifically located by the user's input is concealing a '0' tile...
    else if(board->board_set[rows][cols] == '#' && board->tiles[rows][cols].place_tile == '0'){
        
        board->board_set[rows][cols] = board->tiles[rows][cols].place_tile; //Reveals the targeted tile
        
        //Makes 8 recursion calls to read and possibly reveal the tiles surrounding the originally targeted tile
        reveal_tiles(board, rows - 1, cols - 1);
        
        reveal_tiles(board, rows - 1, cols);
        
        reveal_tiles(board, rows - 1, cols + 1);
        
        reveal_tiles(board, rows, cols + 1);
        
        reveal_tiles(board, rows + 1, cols);
        
        reveal_tiles(board, rows + 1, cols + 1);
        
        reveal_tiles(board, rows + 1, cols - 1);
        
        reveal_tiles(board, rows, cols - 1);
    }

    
    //If the tile targeted by the user's input is concealing a number other than '0', only reveal that tile
    else if(board->board_set[rows][cols] == '#' && board->tiles[rows][cols].place_tile != '0' && board->tiles[rows][cols].place_mine != '*'){
        
        board->board_set[rows][cols] = board->tiles[rows][cols].place_tile;
        
    }
    
    
    //If the tile targeted by the user is concealing a mine, reveal the mine
    else if(board->board_set[rows][cols] == '#' && board->tiles[rows][cols].place_mine == '*'){
        
        board->board_set[rows][cols] = board->tiles[rows][cols].place_mine;
        
    }
}



void execute_action(BOARD* board, int rows, int cols, int action_num){

    //If the user inputs 0 as the action...
    if(action_num == 0){

        reveal_tiles(board, rows, cols); //calls function to reveal tile(s)
    }
    
    //If the user inputs 1 as the action...
    else if(action_num == 1){

        board->board_set[rows][cols] = '?'; //Places a question mark on the targeted tile
    }
    
    //If the user inputs 2 as the action...
    else if(action_num == 2){

        board->board_set[rows][cols] = '!'; //Places a mark on the targeted tile
    }
}



void get_action(BOARD* board, int rows, int cols){
    
    
    int action_num; //declared variable to get action number
    int numActsRead; //declared variable to validate input
    board->next_move = false; //initialized bool variable so that if the user cancels their action, it loops back to get_play
    

    //If user targets a question mark
    if(board->board_set[rows][cols] == '?'){
        
        //Asks user for action until the user cancels out
        do{

            printf("Enter Action\n0. UnQuestion\n1. Cancel\n"); //options for action
            
            printf("Action: ");
            
            numActsRead = scanf("%d", &action_num); //Scans user's input
            
            //If user wants to UnQuestion the tile...
            if(action_num == 0){

                board->board_set[rows][cols] = '#'; //reverts back to a concealed tile

                board->next_move = true; //assigns bool variable as true so that the user may target a new tile

                break; //breaks out of do-while loop
            }

            //If the action is not valid, break out of the loop
            else if(!valid_act(numActsRead, 1, action_num)){

                break;
            }
            
        }while(action_num != 1);
    }
    
    
    //If users targets a tile with a mark...
    else if(board->board_set[rows][cols] == '!'){
        
        //Asks user for action until valid input and cancellation
        do{

            printf("Enter Action\n0. UnMark\n1. Cancel\n"); //Options
            
            printf("Action: ");
            
            numActsRead = scanf("%d", &action_num); //scan's input
            
            //If the user want's to UnMark the tile...
            if(action_num == 0){

                board->board_set[rows][cols] = '#'; //Reverts back to a concealed tile

                board->next_move = true; //allows user to target a new tile

                break; //breaks out of loop
            }

            //If the action is not valid, break out of the loop
            else if(!valid_act(numActsRead, 1, action_num)){

                break;  
            }
            
        }while(action_num != 1);
            
    }
    
    
    //If user targets a normally concealed tile...
    else{

        //Continuosly asks for action until valid input and cancellation
        do{
            printf("Enter Action\n0. Reveal\n1. Question\n2. Mark\n3. Cancel\n"); //Options
        
            printf("Action: ");
        
            numActsRead = scanf("%d", &action_num); //scans input
        
            //If user wants to reveal tiles...
            if(action_num == 0){

                reveal_tiles(board, rows, cols); //calls function to reveal tile(s)

                board->next_move = true; //allows user to target a new tile

                break; //breaks out of loop
            }
        
            //If user wants to question a tile...
            else if(action_num == 1){

                board->board_set[rows][cols] = '?'; //Puts a question in place of '#'

                board->next_move = true; //Allows user to target new tile

                break; //breaks out of loop
            }
            
            //If user wants to mark a tile...
            else if(action_num == 2){

                board->board_set[rows][cols] = '!'; //Places a mark

                board->next_move = true; //Allows user to target new tile

                break; //breaks out of loop
            }

            //If the action is not valid, break out of the loop
            else if(!valid_act(numActsRead, 1, action_num)){

                break; 
            }
        
        }while(action_num != 3);
    }
}



bool valid_act(int numActsRead, int numActsNeed, int action_num){
    
    return action_format(numActsRead, numActsNeed) && action_constraints(action_num); //validates format
    
}



bool action_format(int numActsRead, int numActsNeed){
    
    bool is_valid = true; //variable will return as true of false
    char last_char; //variable assigns last character
    
    //If the number of actions read does not equal the number of actions needed...
    if(numActsRead != numActsNeed){
        
        is_valid = false; //It is not valid
    }
    
    //While the last character is not a new line character...
    do{
        
        scanf("%c", &last_char); //scans character after the input
        
        //If the character is not a blank space
        if(!isspace(last_char)){

            is_valid = false; //Not valid
        }
        
    }while(last_char != '\n');
    
    
    return is_valid;
}



bool action_constraints(int action_num){
    
    return action_num >= 0 && action_num < 4; //action numbers ranged from 0 to 3
}



void get_play(BOARD board, int* rows, int* cols){
    
    int numArgsRead; //Variable declared to red the number of arguments
    
    //while the input is not valid...
    do{
        
        //Asks user for a row and column with the boundaries
        printf("Enter row a row between 0-%d and a column between 0-%d: ", board.num_rows - 1, board.num_cols - 1);
        
        numArgsRead = scanf("%d %d", rows, cols); //scans input
        
    }while(!is_valid(numArgsRead, 2, board, *rows, *cols)); //calls function that validates input
    
}



bool is_valid(int numArgsRead, int numArgsNeed, BOARD board, int rows, int cols){
    
    return valid_format(numArgsRead, numArgsNeed) && play_constraints(board, rows, cols); //returns valid formatting and constraints
    
}



bool valid_format(int numArgsRead, int numArgsNeed){
    
    bool is_valid = true;
    char last_char;
    
    //If number of arguments read does not match the amount needed
    if(numArgsRead != numArgsNeed){
        
        is_valid = false; //Is not valid
    }
    
    //While the lact character is not a new line character...
    do{
        
        scanf("%c", &last_char); //scans last character
        
        //If it isn't blank space
        if(!isspace(last_char)){

            is_valid = false; //is not valid
        }
    }while(last_char != '\n');
    
    
    return is_valid;
}



bool play_constraints(BOARD board, int rows, int cols){
    
    return place_piece(board, rows, cols) && revealed_piece(board, rows, cols); //returns if the place is within the boundaries and the tile hasn't been revealed yet
}


bool revealed_piece(BOARD board, int rows, int cols){
    
    bool valid_tile = true;
    
    //If the tile is marked or questioned
    if(board.board_set[rows][cols] == '!' || board.board_set[rows][cols] == '?'){

        return valid_tile; //It's valid
    }
    
    //If the tile is already revealed
    if(board.board_set[rows][cols] != '#'){

        printf("This tile is already revealed.\n"); //prints this statement

        valid_tile = false; //Is not valid
    }
    
    return valid_tile;
}



bool place_piece(BOARD board, int rows, int cols){
    
    return rows >= 0 && rows < board.num_rows && cols >= 0 && cols < board.num_cols; //Is valid if row or column is now less than 0 and does not exceed the last number
    
}