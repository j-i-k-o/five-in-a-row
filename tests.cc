#include <gtest/gtest.h>
#include "five-in-a-row.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(BoardTest, Init) {
    State state;
    /* make 20x20 board */
    EXPECT_EQ(board_init(&state, 20), 0);
    EXPECT_EQ(state.size, 20);
    EXPECT_EQ(state.turn, PLAYER_1);
    int i, j;
    for(i=0; i<400; i++){
        EXPECT_EQ(state.board[i], EMPTY);
    }
    board_destroy(&state);
}

TEST(BoardTest, LargerThan5) {
    State state;
    EXPECT_EQ(board_init(&state, 0), 1);
    EXPECT_EQ(board_init(&state, 1), 1);
    EXPECT_EQ(board_init(&state, 2), 1);
    EXPECT_EQ(board_init(&state, 3), 1);
    EXPECT_EQ(board_init(&state, 4), 1);
    EXPECT_EQ(board_init(&state, 5), 0);
    EXPECT_EQ(board_init(&state, 99), 0);
    EXPECT_EQ(board_init(&state, 100), 0);
    EXPECT_EQ(board_init(&state, 101), 1);
    board_destroy(&state);
}

TEST(BoardTest, PutPieces) {
    State state;
    EXPECT_EQ(board_init(&state, 10), 0);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 2, 4), 0);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 2, 3), 0);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 3, 8), 0);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 4, 5), 0);
    EXPECT_EQ(state.board[2 * state.size + 4], PLAYER_1);
    EXPECT_EQ(state.board[2 * state.size + 3], PLAYER_2);
    EXPECT_EQ(state.board[3 * state.size + 8], PLAYER_1);
    EXPECT_EQ(state.board[4 * state.size + 5], PLAYER_2);
    board_destroy(&state);
}

TEST(BoardTest, PutPiecesOutOfRange) {
    State state;
    EXPECT_EQ(board_init(&state, 10), 0);
    /* player 1 (error) */
    EXPECT_EQ(board_put(&state, 2, 10), 1);
    EXPECT_EQ(board_put(&state, 10, 2), 1);
    EXPECT_EQ(board_put(&state, 2, -2), 1);
    EXPECT_EQ(board_put(&state, -2, 2), 1);
    /* player 1 (error) */
    EXPECT_EQ(board_put(&state, 2, 12), 1);
    /* player 1 (error) */
    EXPECT_EQ(board_put(&state, 12, 4), 1);
    /* player 1 (error) */
    EXPECT_EQ(board_put(&state, 12, 12), 1);
    /* player 1 (error) */
    EXPECT_EQ(board_put(&state, -2, 4), 1);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 4, 4), 0);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 2, 3), 0);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 3, 8), 0);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 4, 5), 0);
    EXPECT_EQ(state.board[4 * state.size + 4], PLAYER_1);
    EXPECT_EQ(state.board[2 * state.size + 3], PLAYER_2);
    EXPECT_EQ(state.board[3 * state.size + 8], PLAYER_1);
    EXPECT_EQ(state.board[4 * state.size + 5], PLAYER_2);
    board_destroy(&state);
}

TEST(BoardTest, NoEmptySpace) {
    State state;
    EXPECT_EQ(board_init(&state, 6), 0);
    int i;
    for(i=0; i<6; i++){
        /* player 1 */
        EXPECT_EQ(board_put(&state, 0, i), 0);
        /* player 2 */
        EXPECT_EQ(board_put(&state, 1, i), 0);
    }
    for(i=0; i<6; i++){
        /* player 1 */
        EXPECT_EQ(board_put(&state, 2, i), 0);
        /* player 2 */
        EXPECT_EQ(board_put(&state, 3, i), 0);
    }
    for(i=0; i<6; i++){
        /* player 1 */
        EXPECT_EQ(board_put(&state, 4, i), 0);
        /* player 2 */
        EXPECT_EQ(board_put(&state, 5, i), 0);
    }
    /* player 1 */
    EXPECT_EQ(board_put(&state, 5, 0), 3);
    board_destroy(&state);
}

TEST(BoardTest, PutPiecesInOccupiedSpace) {
    State state;
    EXPECT_EQ(board_init(&state, 10), 0);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 4, 4), 0);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 4, 4), 2);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 2, 3), 0);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 4, 4), 2);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 3, 8), 0);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 4, 5), 0);
    EXPECT_EQ(state.board[4 * state.size + 4], PLAYER_1);
    EXPECT_EQ(state.board[2 * state.size + 3], PLAYER_2);
    EXPECT_EQ(state.board[3 * state.size + 8], PLAYER_1);
    EXPECT_EQ(state.board[4 * state.size + 5], PLAYER_2);
    board_destroy(&state);
}

TEST(BoardTest, CheckWinner) {
    State state;
    EXPECT_EQ(board_init(&state, 10), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 1, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 2, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 1, 2), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 2, 2), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 1, 3), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 2, 3), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 1, 4), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */
    EXPECT_EQ(board_put(&state, 2, 4), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 wins*/
    EXPECT_EQ(board_put(&state, 1, 5), 0);
    EXPECT_EQ(board_check_winner(&state), PLAYER_1);
    board_destroy(&state);
}

TEST(BoardTest, CheckWinner2) {
    State state;
    EXPECT_EQ(board_init(&state, 10), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 1, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 1, 2), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */                
    EXPECT_EQ(board_put(&state, 2, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 2, 2), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */                
    EXPECT_EQ(board_put(&state, 3, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 3, 2), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */                
    EXPECT_EQ(board_put(&state, 4, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 4, 2), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 5, 5), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 wins */
    EXPECT_EQ(board_put(&state, 5, 2), 0);
    EXPECT_EQ(board_check_winner(&state), PLAYER_2);
    board_destroy(&state);
}

TEST(BoardTest, CheckWinner3) {
    State state;
    EXPECT_EQ(board_init(&state, 10), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 1, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 4, 3), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */                
    EXPECT_EQ(board_put(&state, 2, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 5, 4), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */                
    EXPECT_EQ(board_put(&state, 3, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 6, 5), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */                
    EXPECT_EQ(board_put(&state, 4, 1), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 */                
    EXPECT_EQ(board_put(&state, 7, 6), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 1 */
    EXPECT_EQ(board_put(&state, 5, 5), 0);
    EXPECT_EQ(board_check_winner(&state), EMPTY);
    /* player 2 wins */
    EXPECT_EQ(board_put(&state, 8, 7), 0);
    EXPECT_EQ(board_check_winner(&state), PLAYER_2);
    board_destroy(&state);
}
