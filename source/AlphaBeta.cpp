#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"

// https://www.chessprogramming.org/Alpha-Beta
// http://www.seanet.com/~brucemo/topics/alphabeta.htm
// alpha: best score that can be forced by some means
// beta: worst-case scenario for the opponent
int Board::alphabeta(int alpha, int beta, int depth)
{
    MoveList list;
    int i, n, value;
    Move_t move, best_move = 0;

    // Check time left every 2048 moves
    if ((searched_moves & 2047) && is_search_time_over())
    {
        return 0;
    }

    int hash_flag = HASH_ALPHA;
    if ((value = probe_hash(depth, alpha, beta, best_move)) != UNKNOWN_SCORE)
    {
        return value;
    }

    if (is_game_over())
    {
        value = -MATE_SCORE + search_ply;
        record_hash(depth, value, HASH_EXACT, best_move);
        return value;
    }

    // Leaf node
    if (depth == 0)
    {
        value = quiesce(alpha, beta);
        record_hash(depth, value, HASH_EXACT, best_move);
        return value;
    }

    MoveGenerator::add_all_moves(list, *this, side_to_move());
    MoveGenerator::score_moves(list, *this);
    n = list.length();

    for (i = 0; i < n; i++)
    {
        searched_moves++;
        list.sort_moves(i);
        move = list[i];
        do_move(move);
        value = -alphabeta(-beta, -alpha, depth - 1);
        undo_move(move);
        if (value >= beta)
        {
            record_hash(depth, beta, HASH_BETA, best_move);
            return beta;  // fail hard beta-cutoff
        }
        if (value > alpha)
        {
            hash_flag = HASH_EXACT;
            best_move = move;
            alpha = value;
        }
    }
    record_hash(depth, alpha, hash_flag, best_move);
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
    MoveGenerator::score_moves(list, *this);
    cout << Output::movelist(list, *this, true, false);
    n = list.length();

    for (i = 0; i < n; i++)
    {
        searched_moves++;
        list.sort_moves(i);
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
