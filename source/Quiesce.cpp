#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"

// https://www.chessprogramming.org/Quiescence_Search
int Board::quiesce(int alpha, int beta)
{
    MoveList list;
    int i, n, value;
    Move_t move;

    int stand_pat = evaluate();
    if (stand_pat >= beta)
    {
        return beta;
    }
    if (alpha < stand_pat)
    {
        alpha = stand_pat;
    }

    MoveGenerator::add_all_moves(list, *this, side_to_move());
    n = list.length();

    for (i = 0; i < n; i++)
    {
        searched_moves++;
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
