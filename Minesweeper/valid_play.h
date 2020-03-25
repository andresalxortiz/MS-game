#ifndef VALID_PLAY_H
    #define VALID_PLAY_H
    
    #include <stdbool.h>
    #include "board_struct.h"
    
    bool game_over(BOARD board);
    bool game_lost(BOARD board);
    bool game_won(BOARD board);
    void declare_winner(BOARD board);
    void reveal_tiles(BOARD* board, int rows, int cols);
    void execute_action(BOARD* board, int rows, int cols, int action_num);
    void get_action(BOARD* board, int rows, int cols);
    void get_play(BOARD board, int* rows, int* cols);
    bool valid_act(int numActsRead, int numActsNeed, int action_num);
    bool action_format(int numActsRead, int numActsNeed);
    bool action_constraints(int action_num);
    bool is_valid(int numArgsRead, int numArgsNeed, BOARD board, int rows, int cols);
    bool valid_format(int numArgsRead, int numArgsNeed);
    bool play_constraints(BOARD board, int rows, int cols);
    bool revealed_piece(BOARD board, int rows, int cols);
    bool place_piece(BOARD board, int rows, int cols);
    

#endif