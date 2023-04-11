#include "Board.h"
#include "MoveList.h"
#include "MoveGenerator.h"

// https://www.chessprogramming.org/Minimax
// This function returns the best score
int Board::minimax(int depth, bool maximizing_player)
{
    MoveList list;
    int i, n, bestvalue, value;
    Move_t move;

    // Leaf node
    if (depth == 0 || is_game_over())
    {
        return evaluate();
    }

    if (maximizing_player == true)
    {
        bestvalue = -INFINITY;

        MoveGenerator::add_all_moves(list, *this, side_to_move());
        n = list.length();

        for (i = 0; i < n; i++)
        {
            searched_moves++;
            move = list[i];
            do_move(move);
            value = minimax(depth - 1, false);
            undo_move(move);
            bestvalue = max(value, bestvalue);
        }
        return bestvalue;
    }
    else
    {
        bestvalue = INFINITY;

        MoveGenerator::add_all_moves(list, *this, side_to_move());
        n = list.length();

        for (i = 0; i < n; i++)
        {
            searched_moves++;
            move = list[i];
            do_move(move);
            value = minimax(depth - 1, true);
            undo_move(move);
            bestvalue = min(value, bestvalue);
        }
        return bestvalue;
    }
}

// This function returns the best move
Move_t Board::minimax_root(int depth, bool maximizing_player)
{
    MoveList list;
    int i, n, bestvalue, value;
    Move_t move, bestmove = 0;

    // Reset searched_moves
    searched_moves = 0;

    if (maximizing_player == true)
    {
        bestvalue = -INFINITY;

        MoveGenerator::add_all_moves(list, *this, side_to_move());
        // cout << Output::movelist(list, *this, false, false);
        n = list.length();

        for (i = 0; i < n; i++)
        {
            searched_moves++;
            move = list[i];
            do_move(move);
            value = minimax(depth - 1, false);
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
    }
    else
    {
        bestvalue = INFINITY;

        MoveGenerator::add_all_moves(list, *this, side_to_move());
        // cout << Output::movelist(list, *this, false, false);
        n = list.length();

        for (i = 0; i < n; i++)
        {
            searched_moves++;
            move = list[i];
            do_move(move);
            value = minimax(depth - 1, true);
            undo_move(move);
            cout << Output::move_fancy(move, *this) << " (" << dec << value << "), ";
            if ((i % 4 == 3) || (i == n - 1))
            {
                cout << endl;
            }
            if (value < bestvalue)
            {
                bestvalue = value;
                bestmove = move;
            }
        }
    }
    return bestmove;
}
