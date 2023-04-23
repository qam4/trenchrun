/*
 * File:   Moves.h
 *
 */

#ifndef MOVES_H
#define MOVES_H

#include "Types.h"

typedef U32 Move_t;

// FLAGS
static const U8 NO_FLAGS = 0;
static const U8 LAST_MOVE_SIDEWAYS_MASK = 3;
static const U8 MOVED_SIDEWAYS = 4;

Move_t inline build_move(U8 from, U8 to) { return (from & 0x3FU) | (to & 0x3FU) << 6; }
Move_t inline build_capture(U8 from, U8 to, U8 capture) { return (from & 0x3FU) | (to & 0x3FU) << 6 | (capture & 0xFU) << 12; }
Move_t inline build_move_flags(U8 from, U8 to, U8 flags) { return (from & 0x3FU) | (to & 0x3FU) << 6 | (flags & 0x7U) << 16; }
Move_t inline build_move_all(U8 from, U8 to, U8 flags, U8 capture) { return (from & 0x3FU) | (to & 0x3FU) << 6 | (capture & 0xFU) << 12 | (flags & 0x7U) << 16; }
void inline move_add_score(Move_t *move, U16 score) { *move = *move | (score & 0x1FFFU) << 19; }

bool inline is_capture(Move_t move) { return (move >> 12) & 0xFU; }

U8 inline move_from(Move_t move) { return move & 0x3FU; }
U8 inline move_to(Move_t move) { return (move >> 6) & 0x3FU; }
U8 inline move_captured(Move_t move) { return (move >> 12) & 0xFU; }
U8 inline move_flags(Move_t move) { return (move >> 16) & 0x7U; }
U16 inline move_score(Move_t move) { return (move >> 19) & 0x1FFFU; }

#endif /* MOVES_H */
