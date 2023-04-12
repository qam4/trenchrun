/*
 * File:   Common.h
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

using namespace std;

#define DEBUG

#include "Types.h"
#include "Constants.h"
#include "Board.h"
#include "Move.h"

// https://www.chessprogramming.org/BitScan
const U8 index64[64] = {
   63,  0, 58,  1, 59, 47, 53,  2,
   60, 39, 48, 27, 54, 33, 42,  3,
   61, 51, 37, 40, 49, 18, 28, 20,
   55, 30, 34, 11, 43, 14, 22,  4,
   62, 57, 46, 52, 38, 26, 32, 41,
   50, 36, 17, 19, 29, 10, 13, 21,
   56, 45, 25, 31, 35, 16,  9, 12,
   44, 24, 15,  8, 23,  7,  6,  5
};

/**
* bitScanForward
* @author Charles E. Leiserson
*         Harald Prokop
*         Keith H. Randall
* "Using de Bruijn Sequences to Index a 1 in a Computer Word"
* @param bb bitboard to scan
* @precondition bb != 0
* @return index (0..63) of least significant one bit
*/
U8 inline bit_scan_forward(U64 bb)
{
#ifdef DEBUG
    assert(bb > 0);
#endif
   const U64 debruijn64 = C64(0x07EDD5E59A4E28C2);
   const U64 neg_bb = (0 - bb);
   return index64[((bb & neg_bb) * debruijn64) >> 58];
}
U64 inline circular_left_shift(U64 target, int shift)
{
#ifdef DEBUG
    assert(shift >= 0);
    assert(shift <= 64);
#endif
    return (target << shift) | (target >> (64 - shift));
}

int pop_count(U64 x);
bool inline is_valid_piece(U8 piece) { return (piece >= WHITE_WALL) && (piece <= BLACK_DEATHSTAR); }
bool inline is_valid_square(int square) { return (square >= 0) && (square <= 64); }
bool is_valid_move(Move_t move, const class Board &board);

#endif /* COMMON_H */
