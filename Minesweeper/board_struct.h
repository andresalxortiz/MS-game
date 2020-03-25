#ifndef BOARD_STRUCT_H
    #define BOARD_STRUCT_H
    
    #include <stdbool.h>

    typedef struct Tiles_Struct{;
        char place_tile;
        char place_mine;
    }TILES;
    
    
    typedef struct Board_Struct{
        TILES** tiles;
        char** board_set;
        int num_rows;
        int num_cols;
        int num_mines;
        bool next_move;
    }BOARD;
    
    
#endif