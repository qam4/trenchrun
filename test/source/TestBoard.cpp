/*
 * File:   TestBoard.cpp
 *
 */

#include <catch2/catch_test_macros.hpp>

#include "Tests.h"

TEST_CASE("board_can_construct", "[board]")
{
    cout << "- Can construct board" << endl;
    Board board = Board();
    REQUIRE(board.is_blank());
}

TEST_CASE("board_can_add_pieces", "[board]")
{
    cout << "- Can add piece" << endl;
    Board board = Board();
    board.add_piece(WHITE_XWING, D5);
    REQUIRE(board[D5] == WHITE_XWING);
    U64 bitboard = 1ULL << D5;
    REQUIRE(board.bitboard(WHITE) & bitboard);
    REQUIRE(board.bitboard(WHITE_XWING) & bitboard);
}

TEST_CASE("board_can_remove_pieces", "[board]")
{
    cout << "- Can remove piece" << endl;
    Board board = Board();
    board.add_piece(BLACK_DEATHSTAR, H4);
    REQUIRE(board[H4] == BLACK_DEATHSTAR);
    board.remove_piece(H4);
    REQUIRE(board[H4] == EMPTY);
    REQUIRE(board.is_blank());
}

TEST_CASE("board_can_reset", "[board]")
{
    cout << "- Can reset board" << endl;
    Board board = Board();
    board.add_piece(WHITE_XWING, D5);
    REQUIRE(board[D5] == WHITE_XWING);
    board.reset();
    REQUIRE(board.is_blank());
}

TEST_CASE("board_is_game_over", "[board]")
{
    cout << "- Board: is game over" << endl;
    Board board = Board();
    REQUIRE(board.is_game_over());
    board.add_piece(WHITE_DEATHSTAR, D2);  // only the deathstar
    REQUIRE(board.is_game_over());
    board.add_piece(WHITE_TIEFIGHTER, D1);  // one piece that can move and the deathstar
    REQUIRE(!board.is_game_over());
    board.remove_piece(D2);  // only one piece that can move
    REQUIRE(board.is_game_over());
    board.reset();

    board.set_side_to_move(BLACK);
    board.add_piece(BLACK_DEATHSTAR, D6);
    REQUIRE(board.is_game_over());
    board.add_piece(BLACK_TIEFIGHTER, D7);
    REQUIRE(!board.is_game_over());
    board.remove_piece(D6);
    REQUIRE(board.is_game_over());
}
