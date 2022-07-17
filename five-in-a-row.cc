#include "five-in-a-row.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

void draw(const State* p_state){
    int r, c;
    for(r=0; r<p_state->size; r++){
        for(c=0; c<p_state->size; c++){
            switch (board_get(p_state, r, c)) {
                case EMPTY:
                    printf("⬜");
                    break;
                case PLAYER_1:
                    printf("１");
                    break;
                case PLAYER_2:
                    printf("２");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    printf("set board size: ");
    int board_size;
    scanf("%d", &board_size);
    State state;
    switch (board_init(&state, board_size)) {
        case 1:
            fprintf(stderr, "Invalid range\n");
            exit(1);
            break;
        default:
            break;
    }

    int game_set = 0;
    while(game_set == 0){
        /*clrscr();*/
        draw(&state);
        printf("Player %d turn [format: r c]: ", state.turn);
        int r, c;
        scanf("%d%d", &r, &c);
        switch (board_put(&state, r, c)) {
            case 1:
                printf("Invalid range\n");
                break;
            case 2:
                printf("Cannot put the piece here\n");
                break;
            case 3:
                printf("No places to put piece\n");
                game_set = 1;
                break;
            default:
                break;
        }

        int winner = board_check_winner(&state);
        if(winner != EMPTY){
            printf("Player %d wins.\n", winner);
            draw(&state);
            game_set = 1;
        }
    }

    board_destroy(&state);
    return 0;
}
