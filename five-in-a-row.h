#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Piece{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};

typedef struct StateStruct{
    int* board;
    int size;
    Piece turn;
} State;


int board_init(State* p_state, int board_size){

    if(board_size < 5 || 100 < board_size){
        return 1;
    }

    p_state->board = (int*)malloc(board_size * board_size * sizeof(int));
    int i;
    for(i=0; i<board_size * board_size; i++){
        p_state->board[i] = EMPTY;
    }
    p_state->size = board_size;
    p_state->turn = PLAYER_1;
    return 0;
}

void board_destroy(State* p_state){
    free(p_state->board);
}

int board_get(const State* p_state, int r, int c){
    return p_state->board[r * p_state->size + c];
}

int board_put(State* p_state, int r, int c){
    
    /* check if specified index is in correct range */
    if(!(0 <= r && r < p_state->size && 0 <= c && c < p_state->size)){
        return 1;
    }

    /* check if there is empty space */
    int i;
    int has_empty_space = 0;
    for(i=0; i<p_state->size * p_state->size; i++){
        if(p_state->board[i] == EMPTY){
            has_empty_space = 1;
            break;
        }
    }
    if(has_empty_space == 0){
        return 3;
    }

    Piece player = p_state->turn;

    /* check if the space is occupied */
    if(board_get(p_state, r, c) != EMPTY){
        return 2;
    }
    
    p_state->board[r * p_state->size + c] = player;

    /* switch turn */
    p_state->turn = player == PLAYER_1 ? PLAYER_2 : PLAYER_1;

    return 0;
}

int board_check_winner(const State* p_state){
    int r, c, cur_r, cur_c, cur_player, num_piece;
    for(r=0; r<p_state->size; r++){
        for(c=0; c<p_state->size; c++){
            if(board_get(p_state, r, c) != EMPTY){
                int player = board_get(p_state, r, c);
                /* go left */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_c--;
                }

                /* go right */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_c++;
                }

                /* go top */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_r--;
                }

                /* go buttom */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_r++;
                }

                /* go lefttop */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_r--;
                    cur_c--;
                }

                /* go righttop */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_r--;
                    cur_c++;
                }

                /* go leftbuttom */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_r++;
                    cur_c--;
                }

                /* go rightbuttom */
                cur_r = r;
                cur_c = c;
                num_piece = 0;
                while(board_get(p_state, cur_r, cur_c) == player){
                    if(!(0 <= cur_r && cur_r < p_state->size && 0 <= cur_c && cur_c < p_state->size)){
                        break;
                    }
                    num_piece++;

                    if(num_piece == 5){
                        return player;
                    }

                    cur_r++;
                    cur_c++;
                }
            }
        }
    }

    return EMPTY;
}


