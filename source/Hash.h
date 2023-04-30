/*
 * File:   Hash.h
 *
 */

#ifndef HASH_H
#define HASH_H

#include "Types.h"
#include "Move.h"

#define HASH_TABLE_SIZE (1024*1024)

#define    HASH_EXACT   0
#define    HASH_ALPHA   1
#define    HASH_BETA    2

typedef struct HASHE_s {
    U64 key;
    int depth;
    int flags;
    int value;
    Move_t best_move;

}   HASHE;

void reset_hash_table();

#endif /* HASH_H */
