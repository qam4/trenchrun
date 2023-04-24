/*
 * File:   Board.cpp
 *
 */

#include "Board.h"

#include "MoveGenerator.h"
#include "MoveList.h"

Board::Board()
{
    reset();
}

bool Board::is_blank()
{
    return !(bitboards[WHITE] | bitboards[BLACK]);
}

void Board::add_piece(U8 piece, int square)
{
#ifdef DEBUG
    assert(is_valid_piece(piece));
    assert(is_valid_square(square));
    assert(board_array[square] == EMPTY);
#endif
    board_array[square] = piece;
    U64 bitboard = 1ULL << square;
    bitboards[piece & 1] |= bitboard;
    bitboards[piece] |= bitboard;
}

void Board::remove_piece(int square)
{
#ifdef DEBUG
    assert(is_valid_square(square));
    assert(board_array[square] != EMPTY);
#endif
    U8 piece = board_array[square];
    board_array[square] = EMPTY;
    U64 bitboard = ~(1ULL << square);
    bitboards[piece & 1] &= bitboard;
    bitboards[piece] &= bitboard;
}

void Board::reset()
{
    for (int i = 0; i < 64; i++)
    {
        board_array[i] = EMPTY;
    }
    for (int i = 0; i < 14; i++)
    {
        bitboards[i] = 0ULL;
    }
    irrev.last_move_sideways = 0;
    irrev.side_to_move = WHITE;
    game_ply = 1;
}

U8 Board::operator[](const int square) const
{
#ifdef DEBUG
    assert(is_valid_square(square));
#endif
    return board_array[square];
}

U64 Board::bitboard(const int type) const
{
#ifdef DEBUG
    assert(type >= 0 && type <= BLACK_DEATHSTAR);
#endif
    return bitboards[type];
}

void Board::do_move(Move_t move)
{
    U8 piece = board_array[move_from(move)];
    // cout << "do_move:" << Output::move_fancy(move, *this) << endl;
    // cout << "do_move: move_flag=" << hex << move << endl;
    // cout << "do_move: last_move_sideways=" <<(int)irrev.last_move_sideways << endl;

    if (is_capture(move))
    {
        remove_piece(move_to(move));
    }
    remove_piece(move_from(move));
    add_piece(piece, move_to(move));

    // update last_move_sideways.
    // First reset the flag, then check if the current move is sideways to set the flag
    irrev.last_move_sideways &= static_cast<U8>(~(1 << irrev.side_to_move));

    if ((move_flags(move) & MOVED_SIDEWAYS) != 0)
        irrev.last_move_sideways |= static_cast<U8>(1 << irrev.side_to_move);
    // cout << "do_move: last_move_sideways=" << (int)irrev.last_move_sideways << endl;

    // update side_to_move
    irrev.side_to_move ^= 1;

    game_ply++;
    search_ply++;
}

void Board::undo_move(Move_t move)
{
    U8 piece = board_array[move_to(move)];
    // cout << "undo_move:" << Output::move_fancy(move, *this) << endl;
    // cout << "undo_move: move_flag=" << hex << move << endl;
    // cout << "undo_move: last_move_sideways=" <<(int)irrev.last_move_sideways << endl;

    // update side_to_move
    irrev.side_to_move ^= 1;

    remove_piece(move_to(move));
    add_piece(piece, move_from(move));
    if (is_capture(move))
    {
        add_piece(move_captured(move), move_to(move));
    }
    // update last_move_sideways
    irrev.last_move_sideways = move_flags(move) & LAST_MOVE_SIDEWAYS_MASK;
    // cout << "undo_move: last_move_sideways=" <<(int)irrev.last_move_sideways << endl;

    game_ply--;
    search_ply--;
}

int Board::evaluate()
{
    /*
    https://www.chessprogramming.org/Evaluation
    f(p) = 200(K-K')
           + 9(Q-Q')
           + 5(R-R')
           + 3(B-B' + N-N')
           + 1(P-P')
           - 0.5(D-D' + S-S' + I-I')
           + 0.1(M-M') + ...

    KQRBNP = number of kings, queens, rooks, bishops, knights and pawns
    D,S,I = doubled, blocked and isolated pawns
    M = Mobility (the number of legal moves)
    */
    int result = 0;
    result = 100 * (pop_count(bitboards[WHITE_DEATHSTAR]) - pop_count(bitboards[BLACK_DEATHSTAR]))
        + 5 * (pop_count(bitboards[WHITE_TIEFIGHTER]) - pop_count(bitboards[BLACK_TIEFIGHTER]))
        + 3 * (pop_count(bitboards[WHITE_XWING] & DARK_SQUARES) - pop_count(bitboards[BLACK_XWING] & DARK_SQUARES))
        + 1 * (pop_count(bitboards[WHITE_XWING] & LIGHT_SQUARES) - pop_count(bitboards[BLACK_XWING] & LIGHT_SQUARES));

    // cout << "evaluate=" << result << endl;
    return result;
}

// is_game_over(): return 1 if game is over.
int Board::is_game_over()
{
    // Game over if:
    // - no legal moves
    // - deathstar captured
    if (bitboards[DEATHSTAR | irrev.side_to_move] == 0)
        return 1;
    MoveList list;
    MoveGenerator::add_all_moves(list, *this, side_to_move());
    if (list.length() == 0)
        return 1;

    return 0;
}

Move_t Board::search(int depth)
{
    search_ply = 0;
#if 0
    Move_t move = minimax_root(depth, side_to_move() == WHITE);
    Move_t move = negamax_root(depth);
#endif
    Move_t move = alphabeta_root(depth);
    return move;
}
