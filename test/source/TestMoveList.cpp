/*
 * File:   TestMoveList.cpp
 *
 */

#include <catch2/catch_test_macros.hpp>

#include "Tests.h"

TEST_CASE("move_list_can_push", "[move list]")
{
    cout << "- Can push" << endl;
    class MoveList list = MoveList();
    REQUIRE(list.length() == 0);
    Move_t move = build_move(A5, B7);
    REQUIRE(list.length() == 0);
    list.push(move);
    REQUIRE(list.length() == 1);
    REQUIRE(list[0] == move);
}

TEST_CASE("move_list_can_reset", "[move list]")
{
    cout << "- Can reset" << endl;
    class MoveList list = MoveList();
    Move_t move = build_move(A5, B7);
    list.push(move);
    REQUIRE(list.length() == 1);
    REQUIRE(list[0] == move);
    list.reset();
    REQUIRE(list.length() == 0);
}

TEST_CASE("move_list_can_pop", "[move list]")
{
    cout << "- Can pop" << endl;
    class MoveList list = MoveList();
    Move_t move = build_move(A5, B7);
    list.push(move);
    Move_t popped = list.pop();
    REQUIRE(list.length() == 0);
    REQUIRE(popped == move);
}
