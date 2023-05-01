/*
 * File:   PrincipalVariation.cpp
 *
 */

#include "PrincipalVariation.h"

#include "Board.h"
#include "MoveList.h"
#include "Output.h"

Move_t pv_table[MAX_PLY * MAX_PLY];
int pv_length[MAX_PLY];

void reset_pv_table()
{
    for (int i = 0; i < MAX_PLY * MAX_PLY; i++)
    {
        pv_table[i] = 0;
    }
    for (int i = 0; i < MAX_PLY; i++)
    {
        pv_length[i] = 0;
    }
}

void Board::print_pv()
{
    for (int i = 0; i < pv_length[0]; i++)
    {
        if ((i == 0) || (game_ply & 1) == 0)
        {
            cout << (game_ply + 2) / 2 << ". ";
        }

        if ((i == 0) && ((game_ply & 1) == 1))
        {
            cout << "... ";
        }

        Move_t move = pv_table[i];
        cout << Output::move_fancy(move, *this) << " ";
        do_move(move);
    }
    for (int i = pv_length[0] - 1; i >= 0; i--)
    {
        Move_t move = pv_table[i];
        undo_move(move);
    }
}

// store PV move
void Board::store_pv_move(Move_t move)
{
    pv_table[search_ply * MAX_PLY + search_ply] = move;
    for (int next_ply = search_ply + 1; next_ply < pv_length[search_ply + 1]; next_ply++)
    {
        pv_table[search_ply * MAX_PLY + next_ply] = pv_table[(search_ply + 1) * MAX_PLY + next_ply];
    }
    pv_length[search_ply] = pv_length[search_ply + 1];
}

// sort PV move
void Board::sort_pv_move(class MoveList& list, Move_t best_move)
{
    // sort hash table move
    for (int i = 0; i < list.length(); i++)
    {
        Move_t move = list[i];
        if (list[i] == best_move)
        {
            move_add_score(&move, 1000);
            return;
        }
    }

    // sort PV move
    if (search_ply && follow_pv)
    {
        follow_pv = 0;
        for (int i = 0; i < list.length(); i++)
        {
            Move_t move = list[i];
            if (move == pv_table[search_ply])
            {
                follow_pv = 1;
                move_add_score(&move, 500);
                break;
            }
        }
    }
}
