/*
 * File:   Hash.cpp
 *
 */

#include "Hash.h"

#include "Board.h"

HASHE hash_table[HASH_TABLE_SIZE];

void reset_hash_table()
{
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        hash_table[i].key = 0;
        hash_table[i].depth = 0;
        hash_table[i].flags = 0;
        hash_table[i].value = 0;
        hash_table[i].best_move = 0;
    }
}

int Board::probe_hash(int depth, int alpha, int beta, Move_t& best_move)
{
    U64 hash = get_hash();
    HASHE* phashe = &hash_table[hash % HASH_TABLE_SIZE];

    if (phashe->key == hash)
    {
        if (phashe->depth >= depth)
        {
            if (phashe->flags == HASH_EXACT)
            {
                return phashe->value;
            }
            if ((phashe->flags == HASH_ALPHA) && (phashe->value <= alpha))
            {
                return alpha;
            }
            if ((phashe->flags == HASH_BETA) && (phashe->value >= beta))
            {
                return beta;
            }
        }

        // RememberBestMove();
        best_move = phashe->best_move;
    }

    return UNKNOWN_SCORE;
}

void Board::record_hash(int depth, int val, int flags, Move_t best_move)
{
    U64 hash = get_hash();
    HASHE* phashe = &hash_table[hash % HASH_TABLE_SIZE];

    phashe->key = hash;
    phashe->best_move = best_move;
    phashe->value = val;
    phashe->flags = flags;
    phashe->depth = depth;
}
