#ifndef BOARD_SETUP_H
    #define BOARD_SETUP_H
    
    #include "board_struct.h"
    
    
    void total_mines(BOARD board);
    void display_layout(BOARD board);
    void display_board(BOARD board);
    TILES** create_layout(BOARD* board, int seedVal);
    char** create_board(BOARD* board);
    void mine_layout(BOARD* board, int seedVal);
    void set_up(BOARD* board);
    void clean_up(BOARD* board);
    
    
#endif