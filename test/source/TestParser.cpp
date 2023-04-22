/*
 * File:   TestParser.cpp
 *
 */

#include <catch2/catch_test_macros.hpp>

#include "Tests.h"

TEST_CASE("parser_can_parse_fen", "[parser]")
{
    cout << "- Can parse FEN test 1" << endl;
    string fen = "++++++++/1TT1TT1+/2~*~2+/XX3XX+/7+/xx3xx+/2+@+2+/1tt1tt1+";
    // clang-format off
    U8 expected_board_A[64] = {
        EMPTY, WHITE_TIEFIGHTER, WHITE_TIEFIGHTER, EMPTY, WHITE_TIEFIGHTER, WHITE_TIEFIGHTER, EMPTY, WHITE_WALL,
        EMPTY, EMPTY, WHITE_WALL, WHITE_DEATHSTAR, WHITE_WALL, EMPTY, EMPTY, WHITE_WALL,
        WHITE_XWING, WHITE_XWING, EMPTY, EMPTY, EMPTY, WHITE_XWING, WHITE_XWING, WHITE_WALL,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WHITE_WALL,
        BLACK_XWING, BLACK_XWING, EMPTY, EMPTY, EMPTY, BLACK_XWING, BLACK_XWING, WHITE_WALL,
        EMPTY, EMPTY, BLACK_WALL, BLACK_DEATHSTAR, BLACK_WALL, EMPTY, EMPTY, WHITE_WALL,
        EMPTY, BLACK_TIEFIGHTER, BLACK_TIEFIGHTER, EMPTY, BLACK_TIEFIGHTER, BLACK_TIEFIGHTER, EMPTY, WHITE_WALL,
        WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL};
    // clang-format on

    Board board = Parser::parse_fen(fen);

    for (int i = 0; i < 64; i++)
    {
        REQUIRE(board[i] == expected_board_A[i]);
    }
    REQUIRE(board.last_move_sideways() == 0);
    REQUIRE(board.side_to_move() == WHITE);
    // cout << Output::board(board) << endl;

    cout << "- Can parse FEN test 2" << endl;
    fen = "++++++++/1TT1TT1+/2~*~2+/XX3XX+/7+/xx3xx+/2+@+2+/1tt1tt1+ b BW";
    // clang-format off
    U8 expected_board_B[64] = {
        EMPTY, WHITE_TIEFIGHTER, WHITE_TIEFIGHTER, EMPTY, WHITE_TIEFIGHTER, WHITE_TIEFIGHTER, EMPTY, WHITE_WALL,
        EMPTY, EMPTY, WHITE_WALL, WHITE_DEATHSTAR, WHITE_WALL, EMPTY, EMPTY, WHITE_WALL,
        WHITE_XWING, WHITE_XWING, EMPTY, EMPTY, EMPTY, WHITE_XWING, WHITE_XWING, WHITE_WALL,
        EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, WHITE_WALL,
        BLACK_XWING, BLACK_XWING, EMPTY, EMPTY, EMPTY, BLACK_XWING, BLACK_XWING, WHITE_WALL,
        EMPTY, EMPTY, BLACK_WALL, BLACK_DEATHSTAR, BLACK_WALL, EMPTY, EMPTY, WHITE_WALL,
        EMPTY, BLACK_TIEFIGHTER, BLACK_TIEFIGHTER, EMPTY, BLACK_TIEFIGHTER, BLACK_TIEFIGHTER, EMPTY, WHITE_WALL,
        WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL, WHITE_WALL};
    // clang-format on

    board = Parser::parse_fen(fen);

    for (int i = 0; i < 64; i++)
    {
        REQUIRE(board[i] == expected_board_B[i]);
    }
    REQUIRE(board.side_to_move() == BLACK);
    REQUIRE(board.last_move_sideways() == (WHITE_MOVED_SIDEWAYS | BLACK_MOVED_SIDEWAYS));
    // cout << Output::board(board) << endl;
}
