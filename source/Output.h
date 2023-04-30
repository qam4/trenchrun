/*
 * File:   Output.h
 * Author: pj
 *
 * Created on January 7, 2013, 11:38 PM
 */

#ifndef OUTPUT_H
#define OUTPUT_H

#include "Common.h"
#include "Board.h"
#include "Move.h"

class Output
{

public:
    static string board(class Board board);
    static string bitboard(U64 bb);
    static string move(Move_t move, const class Board &board);
    static string move_fancy(Move_t move, const class Board &board);
    static string movelist(const class MoveList &list, const class Board &board, bool fancy, bool choice);
    static string board_with_movelist(const class MoveList &list, const class Board &board);
    static string square(U8 square);
    static string piece(U8 piece);
    static void set_colors_enabled(bool enable) { colors_enabled = enable; }
    static bool is_colors_enabled() { return colors_enabled == true; }

private:
    static bool colors_enabled;
};

#endif /* OUTPUT_H */
