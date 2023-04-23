/*
 * File:   MoveList.cpp
 *
 */

#include "MoveList.h"

bool MoveList::contains(Move_t move)
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == move)
            return true;
    }
    return false;
}

bool MoveList::contains_duplicates()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (data[i] == data[j])
                return true;
        }
    }
    return false;
}

bool MoveList::contains_valid_moves(const class Board& board)
{
    for (int i = 0; i < size; i++)
    {
        if (!is_valid_move(data[i], board))
            return false;
    }
    return true;
}

void MoveList::sort_moves(int current_index)
{
    // Selection sort
    for (int i = current_index; i < size; i++)
    {
        U16 current_score = move_score(data[current_index]);
        U16 new_score = move_score(data[i]);
        if (new_score > current_score)
        {
            Move_t tmp = data[current_index];
            data[current_index] = data[i];
            data[i] = tmp;
        }
    }
}
