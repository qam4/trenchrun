#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"

// https://www.chessprogramming.org/Alpha-Beta
int Board::alphabeta(int alpha, int beta, int depth)
{
    MoveList list;
    int i, n, value;
    Move_t move;

    if (is_game_over())
    {
        return -MAX_SCORE;
    }

    // Leaf node
    if (depth == 0)
    {
        int who2move = (side_to_move() == WHITE) ? 1 : -1;
        return who2move * evaluate();
        // return quiesce(alpha, beta);
    }

    MoveGenerator::add_all_moves(list, *this, side_to_move());
    n = list.length();

    for (i = 0; i < n; i++)
    {
        searched_moves++;
        move = list[i];
        do_move(move);
        value = -alphabeta(-beta, -alpha, depth - 1);
        undo_move(move);
        if (value >= beta)
        {
            return beta;  // fail hard beta-cutoff
        }
        alpha = max(value, alpha);
    }
    return alpha;
}

// This function returns the best move
Move_t Board::alphabeta_root(int depth)
{
    MoveList list;
    int i, n, value;
    Move_t move, bestmove = 0;
    int alpha = -MAX_SCORE;
    int beta = MAX_SCORE;

    // Reset searched_moves
    searched_moves = 0;

    MoveGenerator::add_all_moves(list, *this, side_to_move());
    // cout << Output::movelist(list, *this, false, false);
    n = list.length();

    for (i = 0; i < n; i++)
    {
        searched_moves++;
        move = list[i];
        do_move(move);
        value = -alphabeta(-beta, -alpha, depth - 1);
        undo_move(move);
        cout << Output::move_fancy(move, *this) << " (" << dec << value << "), ";
        if ((i % 4 == 3) || (i == n - 1))
        {
            cout << endl;
        }
        if (value >= beta)
        {
            return move;  // fail hard beta-cutoff
        }
        if (value > alpha)
        {
            alpha = value;
            bestmove = move;
        }
    }
    return bestmove;
}
