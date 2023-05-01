#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"
#include "PrincipalVariation.h"

// https://www.chessprogramming.org/Alpha-Beta
// http://www.seanet.com/~brucemo/topics/alphabeta.htm
// alpha: best score that can be forced by some means
// beta: worst-case scenario for the opponent
int Board::alphabeta(int alpha, int beta, int depth)
{
    MoveList list;
    int i, n, value;
    Move_t move, best_move = 0;

    pv_length[search_ply] = search_ply;

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

    // sort PV move
    sort_pv_move(list, best_move);

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
            store_pv_move(move);
        }
    }
    record_hash(depth, alpha, hash_flag, best_move);
    return alpha;
}
