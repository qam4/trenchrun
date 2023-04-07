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
static const U8 MOVED_SIDEWAYS = 1;

Move_t inline build_move(U8 from, U8 to) { return from | (to << 8); }
Move_t inline build_capture(U8 from, U8 to, U8 capture){ return from | (to << 8) | (capture << 24); }
Move_t inline build_move_sideways(U8 from, U8 to){ return from | (to << 8) | (MOVED_SIDEWAYS<<16); }

bool inline is_capture(Move_t move){ return move & (0xFF << 24); }

U8 inline move_from(Move_t move){ return (move & 0xFFULL); }
U8 inline move_to(Move_t move){ return (move & 0xFF00) >> 8; }
U8 inline move_captured(Move_t move){ return (move & 0xFF000000) >> 24; }
U32 inline move_flags(Move_t move){ return (move & 0xFF0000) >> 16; }


#endif /* MOVES_H */
