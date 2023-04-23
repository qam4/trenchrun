#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"

// https://www.chessprogramming.org/Negamax
// This function returns the best score
int Board::negamax(int depth)
{
    MoveList list;
    int i, n, bestvalue, value;
    Move_t move;

    if (is_game_over())
    {
        return -MATE_SCORE + search_ply;
    }

    // Leaf node
    if (depth == 0)
    {
        int who2move = (side_to_move() == WHITE) ? 1 : -1;
        return who2move * evaluate();
    }

    bestvalue = -MAX_SCORE;

    MoveGenerator::add_all_moves(list, *this, side_to_move());
    n = list.length();

    for (i = 0; i < n; i++)
    {
        searched_moves++;
        move = list[i];
        do_move(move);
        value = -negamax(depth - 1);
        undo_move(move);
        bestvalue = max(value, bestvalue);
    }
    return bestvalue;
}

// This function returns the best move
Move_t Board::negamax_root(int depth)
{
    MoveList list;
    int i, n, bestvalue, value;
    Move_t move, bestmove = 0;

    // Reset searched_moves
    searched_moves = 0;

    bestvalue = -MAX_SCORE;

    MoveGenerator::add_all_moves(list, *this, side_to_move());
    // cout << Output::movelist(list, *this, false, false);
    n = list.length();

    for (i = 0; i < n; i++)
    {
        searched_moves++;
        move = list[i];
        do_move(move);
        value = -negamax(depth - 1);
        undo_move(move);
        cout << Output::move_fancy(move, *this) << " (" << dec << value << "), ";
        if ((i % 4 == 3) || (i == n - 1))
        {
            cout << endl;
        }
        if (value > bestvalue)
        {
            bestvalue = value;
            bestmove = move;
        }
    }
    return bestmove;
}
