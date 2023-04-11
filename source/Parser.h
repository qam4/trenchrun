/*
 * File:   Parser.h
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include "Common.h"
#include "Board.h"

class Parser
{
public:
    static class Board parse_fen(string fen);
    static U8 parse_piece(char piece);
    static U8 side(char c);
    static U8 square(char sq[]);
    static U8 last_move_sideways(char c);
    static U32 move(string str, Board &board);

private:
};

#endif /* PARSER_H */
