/*
 * File:   MoveGenerator.h
 *
 */

#ifndef MOVEGENERATOR_H
#define	MOVEGENERATOR_H

#include "Common.h"
#include "MoveList.h"
#include "Move.h"
#include "Board.h"
#include "Output.h"

class MoveGenerator {

public:
	static void add_tiefighter_moves(class MoveList &list, const class Board &board, const int side);
	static void add_xwing_moves(class MoveList &list, const class Board &board, const int side);
	static void add_all_moves(class MoveList &list, const class Board &board, const int side);

	#if 0
	static void add_pawn_pushes(class MoveList &list, const class Board &board, const int side);
    static void add_pawn_double_pushes(class MoveList &list, const class Board &board, const int side);
    static void add_pawn_attacks(class MoveList &list, const class Board &board, const int side);

    static void add_knight_moves(class MoveList &list, const class Board &board, const int side);
    static void add_king_moves(class MoveList &list, const class Board &board, const int side);
    static void generate_move_lookup_tables();
	#endif

private:
    // diff is positive number denoting fixed distance between from and to squares such that:
    // from = (to - diff) % 64
    // ie white pawn push diff = 56, black pawn push diff = 8
    // add_moves assumes moving to blank square
    static void add_moves(U8 from, U64 targets, class MoveList &list, const class Board &board, const U8 flags);
	static void add_moves_check(U8 from, U64 targets, class MoveList &list, const class Board &board, const U8 flags, const U8 side);
    static void add_moves_with_diff(int diff, U64 targets, class MoveList &list, const class Board &board, const U8 flags);
    //static void add_promotions_with_diff(int diff, U64 targets, class MoveList &list, const class Board &board, const U8 flags);
	static U64 byteswap(U64 x);
	static U64 mirrorHorizontal(U64 x);
	static U64 rankMask(int sq);
	static U64 fileMask(int sq);
	static U64 diagMask(int sq);
	static U64 antiDiagMask(int sq);
	static U64 rankMaskEx(int sq);
	static U64 fileMaskEx(int sq);
	static U64 diagMaskEx(int sq);
	static U64 antiDiagMaskEx(int sq);
	static U64 diagAttacks(U64 occ, int sq);
	static U64 antiDiagAttacks(U64 occ, int sq);
	static U64 fileAttacks(U64 occ, int sq);
	static U64 rankAttacks(U64 occ, int sq);
};

#endif	/* MOVEGENERATOR_H */
