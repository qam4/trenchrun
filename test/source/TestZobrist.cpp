/*
 * File:   TestZobrist.cpp
 *
 */

#include <catch2/catch_test_macros.hpp>

#include "Tests.h"

TEST_CASE("zobrist", "[zobrist]")
{
    cout << "Testing Zobrist" << endl;

    // Blank board
    Board board = Board();
    Zobrist zobrist;
    U64 key = zobrist.get_zobrist_key(board);
    REQUIRE(key != 0);

    board.set_side_to_move(BLACK);
    REQUIRE(key != zobrist.get_zobrist_key(board));
    board.set_side_to_move(WHITE);
    REQUIRE(key == zobrist.get_zobrist_key(board));

    board.add_piece(WHITE_TIEFIGHTER, D2);
    REQUIRE(key != zobrist.get_zobrist_key(board));
    board.remove_piece(D2);
    REQUIRE(key == zobrist.get_zobrist_key(board));

    board.set_last_move_sideways(BLACK_MOVED_SIDEWAYS);
    REQUIRE(key != zobrist.get_zobrist_key(board));
    board.set_last_move_sideways(WHITE_MOVED_SIDEWAYS);
    REQUIRE(key != zobrist.get_zobrist_key(board));
    board.set_last_move_sideways(BLACK_MOVED_SIDEWAYS | WHITE_MOVED_SIDEWAYS);
    REQUIRE(key != zobrist.get_zobrist_key(board));
    board.set_last_move_sideways(NO_MOVED_SIDEWAYS);
    REQUIRE(key == zobrist.get_zobrist_key(board));
}
