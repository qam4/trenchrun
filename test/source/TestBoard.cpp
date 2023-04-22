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
