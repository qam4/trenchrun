/*
 * File:   MoveGenerator.cpp
 *
 */

#include "MoveGenerator.h"

#if 0
const U64 KNIGHT_LOOKUP_TABLE[64] = {
        0x0000000000020400ULL, 0x0000000000050800ULL, 0x00000000000A1100ULL, 0x0000000000142200ULL,
        0x0000000000284400ULL, 0x0000000000508800ULL, 0x0000000000A01000ULL, 0x0000000000402000ULL,
        0x0000000002040004ULL, 0x0000000005080008ULL, 0x000000000A110011ULL, 0x0000000014220022ULL,
        0x0000000028440044ULL, 0x0000000050880088ULL, 0x00000000A0100010ULL, 0x0000000040200020ULL,
        0x0000000204000402ULL, 0x0000000508000805ULL, 0x0000000A1100110AULL, 0x0000001422002214ULL,
        0x0000002844004428ULL, 0x0000005088008850ULL, 0x000000A0100010A0ULL, 0x0000004020002040ULL,
        0x0000020400040200ULL, 0x0000050800080500ULL, 0x00000A1100110A00ULL, 0x0000142200221400ULL,
        0x0000284400442800ULL, 0x0000508800885000ULL, 0x0000A0100010A000ULL, 0x0000402000204000ULL,
        0x0002040004020000ULL, 0x0005080008050000ULL, 0x000A1100110A0000ULL, 0x0014220022140000ULL,
        0x0028440044280000ULL, 0x0050880088500000ULL, 0x00A0100010A00000ULL, 0x0040200020400000ULL,
        0x0204000402000000ULL, 0x0508000805000000ULL, 0x0A1100110A000000ULL, 0x1422002214000000ULL,
        0x2844004428000000ULL, 0x5088008850000000ULL, 0xA0100010A0000000ULL, 0x4020002040000000ULL,
        0x0400040200000000ULL, 0x0800080500000000ULL, 0x1100110A00000000ULL, 0x2200221400000000ULL,
        0x4400442800000000ULL, 0x8800885000000000ULL, 0x100010A000000000ULL, 0x2000204000000000ULL,
        0x0004020000000000ULL, 0x0008050000000000ULL, 0x00110A0000000000ULL, 0x0022140000000000ULL,
        0x0044280000000000ULL, 0x0088500000000000ULL, 0x0010A00000000000ULL, 0x0020400000000000ULL,
        };

const U64 KING_LOOKUP_TABLE[64] = {
        0x0000000000000302ULL, 0x0000000000000705ULL, 0x0000000000000E0AULL, 0x0000000000001C14ULL,
        0x0000000000003828ULL, 0x0000000000007050ULL, 0x000000000000E0A0ULL, 0x000000000000C040ULL,
        0x0000000000030203ULL, 0x0000000000070507ULL, 0x00000000000E0A0EULL, 0x00000000001C141CULL,
        0x0000000000382838ULL, 0x0000000000705070ULL, 0x0000000000E0A0E0ULL, 0x0000000000C040C0ULL,
        0x0000000003020300ULL, 0x0000000007050700ULL, 0x000000000E0A0E00ULL, 0x000000001C141C00ULL,
        0x0000000038283800ULL, 0x0000000070507000ULL, 0x00000000E0A0E000ULL, 0x00000000C040C000ULL,
        0x0000000302030000ULL, 0x0000000705070000ULL, 0x0000000E0A0E0000ULL, 0x0000001C141C0000ULL,
        0x0000003828380000ULL, 0x0000007050700000ULL, 0x000000E0A0E00000ULL, 0x000000C040C00000ULL,
        0x0000030203000000ULL, 0x0000070507000000ULL, 0x00000E0A0E000000ULL, 0x00001C141C000000ULL,
        0x0000382838000000ULL, 0x0000705070000000ULL, 0x0000E0A0E0000000ULL, 0x0000C040C0000000ULL,
        0x0003020300000000ULL, 0x0007050700000000ULL, 0x000E0A0E00000000ULL, 0x001C141C00000000ULL,
        0x0038283800000000ULL, 0x0070507000000000ULL, 0x00E0A0E000000000ULL, 0x00C040C000000000ULL,
        0x0302030000000000ULL, 0x0705070000000000ULL, 0x0E0A0E0000000000ULL, 0x1C141C0000000000ULL,
        0x3828380000000000ULL, 0x7050700000000000ULL, 0xE0A0E00000000000ULL, 0xC040C00000000000ULL,
        0x0203000000000000ULL, 0x0507000000000000ULL, 0x0A0E000000000000ULL, 0x141C000000000000ULL,
        0x2838000000000000ULL, 0x5070000000000000ULL, 0xA0E0000000000000ULL, 0x40C0000000000000ULL,
        };
#endif

void MoveGenerator::add_moves(
    U8 from, U64 targets, class MoveList& list, const class Board& board, const U8 flags)
{
    while (targets)
    {
        U8 to = bit_scan_forward(targets);
        U8 capture = board[to];
        Move_t move = build_move_all(from, to, flags, capture);
        list.push(move);
        targets &= targets - 1;
    }
}

void MoveGenerator::add_moves_check(U8 from,
                                    U64 targets,
                                    class MoveList& list,
                                    const class Board& board,
                                    const U8 flags,
                                    const U8 side)
{
    while (targets)
    {
        U8 to = bit_scan_forward(targets);
        U8 capture = board[to];
        Move_t move;
        if (capture != EMPTY)
        {
            // this is a capture, we need to check if the capture is backwards for DEATHSTAR
            if (!(((capture & (~1)) == DEATHSTAR)
                  && (((side == WHITE) && (to > from)) || ((side == BLACK) && (to < from)))))
            {
                // cout << "capture:" <<capture<< endl;
                move = build_move_all(from, to, flags, capture);
                list.push(move);
            }
        }
        else
        {
            // this is a not capture, we need to check if the move is forward
            if (((side == WHITE) && (to > from)) || ((side == BLACK) && (to < from)))
            {
                move = build_move_flags(from, to, flags);
                list.push(move);
            }
        }
        targets &= targets - 1;
    }
}

void MoveGenerator::add_moves_with_diff(
    int diff, U64 targets, class MoveList& list, const class Board& board, const U8 flags)
{
    while (targets)
    {
        U8 to = bit_scan_forward(targets);
        U8 from = static_cast<U8>(to - diff) % 64;
        U8 capture = board[to];
        Move_t move = build_move_all(from, to, flags, capture);
        list.push(move);
        targets &= targets - 1;
    }
}

/**
 * Flip a bitboard vertically about the center ranks.
 * Rank 1 is mapped to rank 8 and vice versa.
 * @param x any bitboard
 * @return bitboard x flipped vertically
 */
U64 MoveGenerator::flipVertical(U64 x)
{
    const U64 k1 = C64(0x00FF00FF00FF00FF);
    const U64 k2 = C64(0x0000FFFF0000FFFF);
    x = ((x >> 8) & k1) | ((x & k1) << 8);
    x = ((x >> 16) & k2) | ((x & k2) << 16);
    x = (x >> 32) | (x << 32);
    return x;
}

/**
 * Byte swap === flip vertical
 */
U64 MoveGenerator::byteswap(U64 x)
{
#if 0
    //  __builtin_bswap64()
    return (__builtin_bswap64(x));
#endif
    return flipVertical(x);
}

/**
 * Mirror a bitboard horizontally about the center files.
 * File a is mapped to file h and vice versa.
 * @param x any bitboard
 * @return bitboard x mirrored horizontally
 *
 * https://www.chessprogramming.org/Flipping_Mirroring_and_Rotating#MirrorHorizontally
 */
U64 MoveGenerator::mirrorHorizontal(U64 x)
{
    const U64 k1 = C64(0x5555555555555555);
    const U64 k2 = C64(0x3333333333333333);
    const U64 k4 = C64(0x0f0f0f0f0f0f0f0f);
    x = ((x >> 1) & k1) | ((x & k1) << 1);
    x = ((x >> 2) & k2) | ((x & k2) << 2);
    x = ((x >> 4) & k4) | ((x & k4) << 4);
    return x;
}

// Sliding piece attacks
// https://www.chessprogramming.org/Sliding_Piece_Attacks

// Ray Masks (should be turned into lookup tables)
U64 MoveGenerator::rankMask(int sq)
{
    return C64(0xff) << (sq & 56);
}

U64 MoveGenerator::fileMask(int sq)
{
    return C64(0x0101010101010101) << (sq & 7);
}

U64 MoveGenerator::diagMask(int sq)
{
    const U64 maindia = C64(0x8040201008040201);
    int diag = 8 * (sq & 7) - (sq & 56);
    int nort = -diag & (diag >> 31);
    int sout = diag & (-diag >> 31);
    return (maindia >> sout) << nort;
}

U64 MoveGenerator::antiDiagMask(int sq)
{
    const U64 maindia = C64(0x0102040810204080);
    int diag = 56 - 8 * (sq & 7) - (sq & 56);
    int nort = -diag & (diag >> 31);
    int sout = diag & (-diag >> 31);
    return (maindia >> sout) << nort;
}
// excluding the square bit:
U64 MoveGenerator::rankMaskEx(int sq)
{
    return (C64(1) << sq) ^ rankMask(sq);
}
U64 MoveGenerator::fileMaskEx(int sq)
{
    return (C64(1) << sq) ^ fileMask(sq);
}
U64 MoveGenerator::diagMaskEx(int sq)
{
    return (C64(1) << sq) ^ diagMask(sq);
}
U64 MoveGenerator::antiDiagMaskEx(int sq)
{
    return (C64(1) << sq) ^ antiDiagMask(sq);
}

#if 0
U64 MoveGenerator::tiefighterMask  (int sq) {return rankMask(sq)     | fileMask(sq);}
U64 MoveGenerator::xwingMask       (int sq) {return diagonalMask(sq) | antiDiagMask(sq);}
U64 MoveGenerator::tiefighterMaskEx(int sq) {return rankMask(sq)     ^ fileMask(sq);}
U64 MoveGenerator::xwingMaskEx     (int sq) {return diagonalMask(sq) ^ antiDiagMask(sq);}
#endif

// https://www.chessprogramming.org/Efficient_Generation_of_Sliding_Piece_Attacks
U64 MoveGenerator::diagAttacks(U64 occ, int sq)
{
    // lineAttacks = (o-2s) ^ (o'-2s')'
    //     with m=mask
    // lineAttacks=(((o&m)-2s) ^ ((o&m)'-2s')')&m
    U64 forward, reverse, slider, lineMask;

    lineMask = diagMaskEx(sq);  // excludes square of slider
    slider = C64(1) << sq;      // singleBitboard[sqOfSlider]; // single bit 1 << sq, 2^sq

    forward = occ & lineMask;     // also performs the first subtraction by clearing the s in o
    reverse = byteswap(forward);  // o'-s'
    forward -= (slider);          // o -2s
    reverse -= byteswap(slider);  // o'-2s'
    forward ^= byteswap(reverse);
    forward &= lineMask;  // mask the line again
    return forward;
}

U64 MoveGenerator::antiDiagAttacks(U64 occ, int sq)
{
    // lineAttacks= (o-2s) ^ (o'-2s')'
    //     with m=mask
    // lineAttacks=(((o&m)-2s) ^ ((o&m)'-2s')')&m
    U64 forward, reverse, slider, lineMask;

    lineMask = antiDiagMaskEx(sq);  // excludes square of slider
    slider = C64(1) << sq;          // singleBitboard[sqOfSlider]; // single bit 1 << sq, 2^sq

    forward = occ & lineMask;     // also performs the first subtraction by clearing the s in o
    reverse = byteswap(forward);  // o'-s'
    forward -= (slider);          // o -2s
    reverse -= byteswap(slider);  // o'-2s'
    forward ^= byteswap(reverse);
    forward &= lineMask;  // mask the line again
    return forward;
}

U64 MoveGenerator::fileAttacks(U64 occ, int sq)
{
    // lineAttacks= (o-2s) ^ (o'-2s')'
    //     with m=mask
    // lineAttacks=(((o&m)-2s) ^ ((o&m)'-2s')')&m
    U64 forward, reverse, slider, lineMask;

    lineMask = fileMaskEx(sq);  // excludes square of slider
    slider = C64(1) << sq;      // singleBitboard[sqOfSlider]; // single bit 1 << sq, 2^sq

    forward = occ & lineMask;     // also performs the first subtraction by clearing the s in o
    reverse = byteswap(forward);  // o'-s'
    forward -= (slider);          // o -2s
    reverse -= byteswap(slider);  // o'-2s'
    forward ^= byteswap(reverse);
    forward &= lineMask;  // mask the line again
    return forward;
}

U64 MoveGenerator::rankAttacks(U64 occ, int sq)
{
    // lineAttacks= (o-2s) ^ (o'-2s')'
    //     with m=mask
    // lineAttacks=(((o&m)-2s) ^ ((o&m)'-2s')')&m
    U64 forward, reverse, slider, lineMask;

    lineMask = rankMaskEx(sq);  // excludes square of slider
    slider = C64(1) << sq;      // singleBitboard[sqOfSlider]; // single bit 1 << sq, 2^sq

    forward = occ & lineMask;  // also performs the first subtraction by clearing the s in o
    reverse = mirrorHorizontal(forward);  // o'-s'
    forward -= (slider);                  // o -2s
    reverse -= mirrorHorizontal(slider);  // o'-2s'
    forward ^= mirrorHorizontal(reverse);
    forward &= lineMask;  // mask the line again
    return forward;
}

void MoveGenerator::add_tiefighter_moves(class MoveList& list,
                                         const class Board& board,
                                         const U8 side)
{
    U64 tiefighters = board.bitboards[TIEFIGHTER | side];
    U64 occupied = board.bitboards[WHITE] | board.bitboards[BLACK];
    U64 friendly = board.bitboards[side] | board.bitboards[BLACK_WALL] | board.bitboards[WHITE_WALL]
        | BOARD_LIMITS;  // own pieces and walls

#if 0
    cout << "tiefighters=0x" << hex << tiefighters<< endl;
    cout << Output::bitboard(tiefighters);
    cout << "occupied=0x" << hex << occupied<< endl;
    cout << Output::bitboard(occupied);
    cout << "friendly=0x" << hex << occupied<< endl;
    cout << Output::bitboard(friendly);
#endif

    while (tiefighters)
    {
        U8 from = bit_scan_forward(tiefighters);

        U64 targets;
        // Can only go sideways if it was not done before.
        if ((board.last_move_sideways() & (1 << side)) == 0)
        {
            targets = rankAttacks(occupied, from);
            targets &= ~(friendly | board.bitboards[DEATHSTAR | !side]);
            add_moves(from, targets, list, board, MOVED_SIDEWAYS | board.last_move_sideways());
        }
        // Add file attacks, can only move backwards if capture
        targets = fileAttacks(occupied, from);
        targets &= ~(friendly);
        add_moves_check(from, targets, list, board, NO_FLAGS | board.last_move_sideways(), side);

        tiefighters &= tiefighters - 1;
    }
    // cout << "found " <<dec<<list.length() << " moves" << endl;
}

void MoveGenerator::add_xwing_moves(class MoveList& list, const class Board& board, const U8 side)
{
    U64 xwings = board.bitboards[XWING | side];
    U64 occupied = board.bitboards[WHITE] | board.bitboards[BLACK];
    U64 friendly = board.bitboards[side] | board.bitboards[BLACK_WALL] | board.bitboards[WHITE_WALL]
        | BOARD_LIMITS;  // own pieces and walls

    while (xwings)
    {
        U8 from = bit_scan_forward(xwings);

        U64 targets;
        // Add diagonal and antidiagonal attacks, can only move backwards if capture
        targets = diagAttacks(occupied, from) + antiDiagAttacks(occupied, from);
        targets &= ~(friendly);
        add_moves_check(from, targets, list, board, NO_FLAGS | board.last_move_sideways(), side);

        xwings &= xwings - 1;
    }
}

void MoveGenerator::add_all_moves(class MoveList& list, const class Board& board, const U8 side)
{
    add_tiefighter_moves(list, board, side);
    add_xwing_moves(list, board, side);
}

void MoveGenerator::score_moves(class MoveList& list, const class Board& board)
{
    int n = list.length();

    for (int i = 0; i < n; i++)
    {
        Move_t move = list[i];
        U8 from = move_from(move);
        U8 to = move_to(move);
        U16 score = MVVLVA[board[to] >> 1][board[from] >> 1];

        // Special case
        // xwing on same square color (DARK) as the deathstar is worth more
        // since it can capture the deathstar
        if ((board[to] & (~1)) == XWING)
        {
            int row = (to & 56) >> 3;
            int file = to & 7;
            int square_color = (row + file) & 1;

            if (square_color == 0)
            {
                score += 1;
            }
        }

        move_add_score(&move, score);
        list.set_move(i, move);
    }
}

#if 0
void MoveGenerator::add_pawn_pushes(class MoveList &list, const class Board &board, const int side){
    const int diffs[2]                   = {8, 64-8};
    const U64 promotions_mask[2]         = {ROW_8, ROW_1};
    const U64 start_row_plus_one_mask[2] = {ROW_3, ROW_6};
    U64 pushes, double_pushes, promotions, pawns, free_squares;

    int diff = diffs[side];
    pawns = board.bitboards[side | PAWN];
    free_squares = ~(board.bitboards[WHITE] | board.bitboards[BLACK]);
    // ADD SINGLE PUSHES
    pushes = circular_left_shift(pawns, diff) & free_squares;
    add_moves_with_diff(diff, pushes & (~promotions_mask[side]), list, board, NO_FLAGS);
    // ADD PROMOTIONS
    promotions = pushes & promotions_mask[side];
    add_promotions_with_diff(diff, promotions, list, board, side);
    // ADD DOUBLE PUSHES
    double_pushes = circular_left_shift(pushes & start_row_plus_one_mask[side], diff) & free_squares;
    add_moves_with_diff(diff+diff, double_pushes, list, board, PAWN_DOUBLE_PUSH);
}

void MoveGenerator::add_pawn_attacks(class MoveList &list, const class Board &board, const int side){
    const int diffs[2][2]        = {{7, 64-9}, {9, 64-7}};
    const U64 promotions_mask[2] = {ROW_8, ROW_1};
    const U64 file_mask[2]       = {~FILE_H, ~FILE_A};
    U64 attacks, ep_attacks, promotions, targets, pawns, enemy;

    pawns = board.bitboards[side | PAWN];
    enemy = board.bitboards[!side];

    // CALCULATE ATTACKS FOR LEFT, RIGHT
    for (int dir = 0; dir < 2; dir++){
        int diff =  diffs[dir][side];
        targets = circular_left_shift(pawns, diff) & file_mask[dir];

        // ADD ATTACKS
        attacks = enemy & targets;
        add_moves_with_diff(diff, attacks & (~promotions_mask[side]), list, board, NO_FLAGS);

        // ADD EP ATTACKS
        ep_attacks = targets & (1ULL << board.irrev.ep_square);
        add_moves_with_diff(diff, ep_attacks, list, board, EP_CAPTURE | (PAWN|(!side)));

        // ADD PROMOTION ATTACKS
        promotions = attacks & promotions_mask[side];
        add_promotions_with_diff(diff, promotions, list, board, side);
    }
}

void MoveGenerator::add_promotions_with_diff(int diff, U64 targets, class MoveList& list, const class Board &board, const U32 side){
    U32 flags = side << 16; // move to third byte
    while(targets){
        U32 to = bit_scan_forward(targets);
        U32 from = ((U32)(to - diff)) % 64;
        U32 capture = board[to];
        U32 move = build_move_all(from, to, flags, capture);
        list.push(move | (KNIGHT << 16));
        list.push(move | (BISHOP << 16));
        list.push(move | (ROOK   << 16));
        list.push(move | (QUEEN  << 16));
        targets &= targets - 1;
    }
}

void MoveGenerator::add_knight_moves(class MoveList &list, const class Board &board, const int side){
    U64 knights = board.bitboards[KNIGHT|side];
    U64 non_friendly = ~board.bitboards[side];
    while(knights){
        U8 from = bit_scan_forward(knights);
        U64 targets = KNIGHT_LOOKUP_TABLE[from] & non_friendly;
        add_moves(from, targets, list, board, NO_FLAGS);
        knights &= knights - 1;
    }
}

void MoveGenerator::add_king_moves(class MoveList &list, const class Board &board, const int side){
    U64 kings = board.bitboards[KING|side];
    U64 non_friendly = ~board.bitboards[side];
    while(kings){
        U8 from = bit_scan_forward(kings);
        U64 targets = KING_LOOKUP_TABLE[from] & non_friendly;
        add_moves(from, targets, list, board, NO_FLAGS);
        kings &= kings - 1;
    }
}

void MoveGenerator::generate_move_lookup_tables(){
    cout << "GENERATING LOOKUP TABLES FOR KNIGHT MOVES" << endl;
    cout << "const U64 KNIGHT_LOOKUP_TABLE[64] = {" << endl << '\t';
    for(int row = 0; row < 8; row++){
        for(int file = 0; file < 8; file++){
            int square = row*8 + file;
            // calculate each one individually starting with up1 left2 and working clockwise
            U64 targets = 0ULL;
            if (file >= 2 && row <= 6) { targets |= 1ULL << (square + 8 - 2); }
            if (file >= 1 && row <= 5) { targets |= 1ULL << (square + 16 - 1); }
            if (file <= 6 && row <= 5) { targets |= 1ULL << (square + 16 + 1); }
            if (file <= 5 && row <= 6) { targets |= 1ULL << (square + 8 + 2); }
            if (file >= 2 && row >= 1) { targets |= 1ULL << (square - 8 - 2); }
            if (file >= 1 && row >= 2) { targets |= 1ULL << (square - 16 - 1); }
            if (file <= 6 && row >= 2) { targets |= 1ULL << (square - 16 + 1); }
            if (file <= 5 && row >= 1) { targets |= 1ULL << (square - 8 + 2); }
            printf("0x%016llXULL", targets);
            cout << ", ";
            if (file == 3) cout << endl << '\t';
        }
        cout << endl << '\t';
    }
    cout << "};" << endl;
    cout << "GENERATING LOOKUP TABLES FOR KING MOVES" << endl;
    cout << "const U64 KING_LOOKUP_TABLE[64] = {" << endl << '\t';
    for(int row = 0; row < 8; row++){
        for(int file = 0; file < 8; file++){
            int square = row*8 + file;
            // calculate each one individually starting with up1 left1 and working clockwise
            U64 targets = 0ULL;
            if(file >= 1 && row <= 6) targets |= 1ULL << (square + 7);
            if(row <= 6) targets |= 1ULL << (square + 8);
            if(file <= 6 && row <= 6) targets |= 1ULL << (square + 9);
            if(file <= 6) targets |= 1ULL << (square + 1);
            if(file <= 6 && row >= 1) targets |= 1ULL << (square - 7);
            if(row >= 1) targets |= 1ULL << (square - 8);
            if(file >= 1 && row >= 1) targets |= 1ULL << (square - 9);
            if(file >= 1) targets |= 1ULL << (square - 1);
            printf("0x%016llXULL", targets);
            cout << ", ";
            if (file == 3) cout << endl << '\t';
        }
        cout << endl << '\t';
    }
    cout << "};" << endl;
}
#endif
