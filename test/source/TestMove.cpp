/*
 * File:   TestMove.cpp
 *
 */

#include <catch2/catch_test_macros.hpp>

#include "Tests.h"

TEST_CASE("move", "[move]")
{
    cout << "Testing Move_t helper functions" << endl;
    Move_t move;
    // test normal move
    move = build_move(A3, A4);
    REQUIRE(move_from(move) == A3);
    REQUIRE(move_to(move) == A4);
    REQUIRE(!is_capture(move));
    REQUIRE(!move_flags(move));

    // test capture
    move = build_capture(A3, B4, BLACK_TIEFIGHTER);
    REQUIRE(move_from(move) == A3);
    REQUIRE(move_to(move) == B4);
    REQUIRE(move_captured(move) == BLACK_TIEFIGHTER);
    REQUIRE(!move_flags(move));
}
