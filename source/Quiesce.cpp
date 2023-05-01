#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"
#include "PrincipalVariation.h"

// https://www.chessprogramming.org/Quiescence_Search
int Board::quiesce(int alpha, int beta)
{
    MoveList list;
    int i, n, value;
    Move_t move;

    pv_length[search_ply] = search_ply;

    // Check time left every 2048 moves
    if ((searched_moves & 2047) && is_search_time_over())
    {
        return 0;
    }

    int who2move = (side_to_move() == WHITE) ? 1 : -1;
    int stand_pat = who2move * evaluate();

    if (search_ply > MAX_PLY - 1)
    {
        return stand_pat;
    }

    if (stand_pat >= beta)
    {
        return beta;
    }
    if (alpha < stand_pat)
    {
        alpha = stand_pat;
    }

    if (is_game_over())
    {
        return -MATE_SCORE + search_ply;
    }

    MoveGenerator::add_all_moves(list, *this, side_to_move());
    MoveGenerator::score_moves(list, *this);
    n = list.length();

    // sort PV move
    sort_pv_move(list, 0);

    for (i = 0; i < n; i++)
    {
        searched_moves++;
        list.sort_moves(i);
        move = list[i];
        if (is_capture(move))
        {
            do_move(move);
            value = -quiesce(-beta, -alpha);
            undo_move(move);
            if (value >= beta)
            {
                return beta;
            }
            alpha = max(value, alpha);
        }
    }
    return alpha;
}
