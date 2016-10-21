/*
 * File:   Common.h
 *
 */

#ifndef COMMON_H
#define	COMMON_H

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

/* __builtin_ffsll returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero */
U32 inline bit_scan_forward(U64 bb) { return __builtin_ffsll(bb)-1; }
U64 inline circular_left_shift(U64 target, int shift){
  #ifdef DEBUG
    assert(shift >= 0);
    assert(shift <= 64);
  #endif
    return (target << shift) | (target >> (64-shift));
}

int pop_count(U64 x);
bool inline is_valid_piece(U8 piece){ return (piece >= WHITE_WALL) && (piece <= BLACK_DEATHSTAR); }
bool inline is_valid_square(int square){ return (square >= 0) && (square <= 64); }
bool is_valid_move(Move_t move, const class Board &board);

#endif	/* COMMON_H */
