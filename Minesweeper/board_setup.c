#include <stdio.h>
#include <stdlib.h>

#include "board_setup.h"
#include "valid_play.h"
#include "board_struct.h"
    

void total_mines(BOARD board){
    
    int i, j;
    int count = 0; //Variable counts each mark
    

    //Nested for loop goes through the whole board in search of marks
    for(i = 0; i < board.num_rows; ++i){
        for(j = 0; j < board.num_cols; ++j){
            
            //If the function encounters a mark
            if(board.board_set[i][j] == '!'){

                count = count + 1; //Add one to count
            }
            
        }
    }
    
    //prints total amount of mines on the board subtracted by the number of marks placed
    printf("There are %d mines left\n", board.num_mines - count);
}



void display_layout(BOARD board){
    
    int i, j;
    int total_rows = board.num_rows - 1; //represents the last row
    

    //Nested for loop prints each element
    for(i = board.num_rows - 1; i >= 0; --i){

        printf("%d ", total_rows); //First prints the number of rows, starting from the last number to 0

        for(j = 0; j < board.num_cols; ++j){
            
            //If the function does not encounter a mine...
            if(board.tiles[i][j].place_mine != '*'){

                printf("%c ", board.tiles[i][j].place_tile); //Prints the numbered tile

                continue; //continues with iteration
            }


            //If the function does encounter a mine...
            else if(board.tiles[i][j].place_mine == '*'){

                printf("%c ", board.tiles[i][j].place_mine); //Prints the mine

            }
        }


        printf("\n"); //Goes on to the next line
        --total_rows; //suntracts one from numbered rows until it reaches 0
    }



    printf("  "); //Space for numbered columns
    for(i = 0; i < board.num_cols; ++i){
        
        printf("%d ", i); //Prints numbered columns
        
    }
    printf("\n"); //Goes on the the next line
}



void display_board(BOARD board){
    
    int i, j;
    int total_rows = board.num_rows - 1; //represents the last row
    
    //Nested for loop displays each element
    for(i = board.num_rows - 1; i >= 0; --i){

        printf("%d ", total_rows); //First prints the number of rows

        for(j = 0; j < board.num_cols; ++j){
            
            printf("%c ", board.board_set[i][j]); //displays each character in each row and column
            
        }

        printf("\n"); //Goes on to the next line
        --total_rows; //subtracts one from the numbered rows until it reaches 0
    }


    printf("  "); //space for numbered columns
    for(i = 0; i < board.num_cols; ++i){
        
        printf("%d ", i); //prints each number of columns
        
    }
    printf("\n"); //Goes on to the next line
}



TILES** create_layout(BOARD* board, int seedVal){
    
    //mallocates for the number of rows the user entered
    board->tiles = (TILES**)malloc(board->num_rows * sizeof(TILES*));
    int m, i, j, row, col;
    srand(seedVal); //uses the seed value to generate random numbers
    
    
    //mallocates for the number of column per row
    for(i = 0; i < board->num_rows; ++i){
        
        board->tiles[i] = (TILES*)malloc(board->num_cols * sizeof(TILES));
    }
    
    
    //m represent the number of mines that have been correctly place
    //While not all mines have been placed...
    while(m != board->num_mines){
        
        i = (rand() % board->num_rows); //generates a random number for a row
        j = (rand() % board->num_cols); //generates a random number for a column
        
        //If the randomly targeted position does not already have a mine
        if(board->tiles[i][j].place_mine != '*'){

            board->tiles[i][j].place_mine = '*'; //Place the mine

            //Indicate the position in which the mine is being placed
            printf("Placing mine at %d", i);
            printf(", %d\n", j);

            //Add one to m
            m += 1;
        }
    }
    

    //Nest for loops reads the whole board in order to place a tile
    for(i = board->num_rows - 1; i >= 0; --i){
        for(j = 0; j < board->num_cols; ++j){
            

            //If a mine hasn't been placed...
            if(board->tiles[i][j].place_mine != '*'){
                
                board->tiles[i][j].place_tile = '0'; //Place a '0' tile
            }
            
            //Otherwise, continue with the iterations
            else{
                
                continue;
            }
        }
    }
    
    
    //Second nested for loops searches through the entire board again generate correct numbered tiles
    for(i = board->num_rows - 1; i >= 0; --i){
        for(j = 0; j < board->num_cols; ++j){

            //If there isn't a mine, continue with the iterations
            if(board->tiles[i][j].place_mine != '*'){

                continue;
            }
            
            //If there is a mine look at the surrounding tiles...
            else{

                //Adds -1, 0, or 1 to j to indictes the bottom, current, and top row respectively  
                for(row = -1; row <= 1; ++row){
                    
                    //If the function goes out of bounds, continue with the iteration
                    if(i + row >= board->num_rows || i + row < 0){
                        continue;
                    }
                    
                    //Adds -1, 0, or 1 to j to indictes the previous, current, and next column respectively    
                    for(col = -1; col <=1; ++col){
                        
                        //If out of bounds, continue with iteration
                        if(j + col >= board->num_cols || j + col < 0){
                            continue;
                        }
                        
                        //If the function encounters another mine, continue with iteration
                        else if(board->tiles[i + row][j + col].place_mine == '*'){

                            continue;
                        }
                        
                        //If the function is not a mine, add + 1 to the numbered tile
                        else{

                            //If tile represent '0' it becomes '1' and so on
                            board->tiles[i + row][j + col].place_tile = board->tiles[i + row][j + col].place_tile + 1; 
                        }
                        
                    }
                }
            }
        }
    }
    
    
    return board->tiles; //returns board with mine layout
}




char** create_board(BOARD* board){
    
    //mallocates for the number of rows the user entered
    board->board_set = (char**)malloc(board->num_rows * sizeof(char*));
    int i, j;
    
    
    //mallocates the number of columns the user entered per row
    for(i = 0; i < board->num_rows; ++i){

        board->board_set[i] = (char*)malloc(board->num_cols * sizeof(char));
    }
    
    
    //Places a concealed tile in each per element
    for(i = 0; i < board->num_rows; ++i){
        for(j = 0; j < board->num_cols; ++j){

            board->board_set[i][j] = '#';
        }
    }
    
    
    return board->board_set; //returns the board
}



void mine_layout(BOARD* board, int seedVal){
    
    board->tiles = create_layout(board, seedVal); //creates board with numbered tiles and mines
    
}



void set_up(BOARD* board){
    
    board->board_set = create_board(board); //creates board
    
}



void clean_up(BOARD* board){
    
    int i;
    
    //Deallocates the number of columns per row
    for(i = 0; i < board->num_rows; ++i){
        
        free(board->board_set[i]);
        free(board->tiles[i]);
        
    }
    
    //Deallocates the number of rows
    free(board->board_set);
    free(board->tiles);
    
    //Set each board to NULL
    board->board_set = NULL;
    board->tiles = NULL;
}