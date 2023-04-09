/*
 * File:   Board.h
 *
 */

#ifndef BOARD_H
#define BOARD_H

#include "Common.h"
#include "Move.h"

class Board
{
    friend class MoveGenerator;
    friend class Tests;

private:
    U64 bitboards[14];
    U8 board_array[64];

    struct IrreversibleData
    {
        U8 side_to_move;
        U8 last_move_sideways;
    } irrev;

    int searched_moves;

public:
    Board();
    bool is_blank();
    void add_piece(U8 piece, int square);
    void remove_piece(int square);
    void reset();
    void do_move(Move_t move);
    void undo_move(Move_t move);
    int evaluate();
    int is_game_over();
    // Algos
    int minimax(int depth, bool maximizing_player);
    Move_t minimax_root(int depth, bool maximizing_player);
    int negamax(int depth);
    Move_t negamax_root(int depth);

    U8 operator[](const int square) const; // return piece on that square
    U64 bitboard(const int type) const;
    U8 side_to_move() const { return irrev.side_to_move; };
    U8 last_move_sideways() const { return irrev.last_move_sideways; };
    void set_side_to_move(U8 side) { irrev.side_to_move = side; };
    void set_last_move_sideways(U8 val) { irrev.last_move_sideways = val; };
    int get_searched_moves() const { return searched_moves; };
};

#endif /* BOARD_H */
