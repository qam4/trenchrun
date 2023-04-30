/*
 * File:   Constants.h
 *
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Common.h"

/*
   Initial position

7  - T T - T T - (BLACK)
6  - - ~ * ~ - -
5  X X - - - X X
4  - - - - - - -
3  x x - - - x x
2  - - + @ + - -
1  - t t - t t -  (WHITE)

   A B C D E F G
*/

const int UNKNOWN_SCORE = 5000;
const int MAX_SCORE = 2000;
const int MATE_SCORE = 1000;
const int MAX_PLY = 64;

const int MAX_SEARCH_TIME = 1000000; // max search time in usec

// PIECES
const U8 EMPTY = 0;

const U8 WHITE = 0;
const U8 BLACK = 1;

const U8 WALL = 2;
const U8 XWING = 4;
const U8 TIEFIGHTER = 6;
const U8 DEATHSTAR = 8;

const U8 WHITE_WALL = 2;       // +
const U8 BLACK_WALL = 3;       // ~
const U8 WHITE_XWING = 4;      // x
const U8 BLACK_XWING = 5;      // X
const U8 WHITE_TIEFIGHTER = 6; // t
const U8 BLACK_TIEFIGHTER = 7; // T
const U8 WHITE_DEATHSTAR = 8;  // @
const U8 BLACK_DEATHSTAR = 9;  // *
const int NUM_PIECES = 10;

const string PIECE_CHARS = "-E+~xXtT@*";

//
const U8 NO_MOVED_SIDEWAYS = 0;
const U8 WHITE_MOVED_SIDEWAYS = 1;
const U8 BLACK_MOVED_SIDEWAYS = 2;

// SQUARES
const U64 LIGHT_SQUARES = C64(0x55AA55AA55AA55AA);
const U64 DARK_SQUARES = C64(0xAA55AA55AA55AA55);

const int A1 = 0;
const int B1 = 1;
const int C1 = 2;
const int D1 = 3;
const int E1 = 4;
const int F1 = 5;
const int G1 = 6;
const int H1 = 7;

const int A2 = 8;
const int B2 = 9;
const int C2 = 10;
const int D2 = 11;
const int E2 = 12;
const int F2 = 13;
const int G2 = 14;
const int H2 = 15;

const int A3 = 16;
const int B3 = 17;
const int C3 = 18;
const int D3 = 19;
const int E3 = 20;
const int F3 = 21;
const int G3 = 22;
const int H3 = 23;

const int A4 = 24;
const int B4 = 25;
const int C4 = 26;
const int D4 = 27;
const int E4 = 28;
const int F4 = 29;
const int G4 = 30;
const int H4 = 31;

const int A5 = 32;
const int B5 = 33;
const int C5 = 34;
const int D5 = 35;
const int E5 = 36;
const int F5 = 37;
const int G5 = 38;
const int H5 = 39;

const int A6 = 40;
const int B6 = 41;
const int C6 = 42;
const int D6 = 43;
const int E6 = 44;
const int F6 = 45;
const int G6 = 46;
const int H6 = 47;

const int A7 = 48;
const int B7 = 49;
const int C7 = 50;
const int D7 = 51;
const int E7 = 52;
const int F7 = 53;
const int G7 = 54;
const int H7 = 55;

const int A8 = 56;
const int B8 = 57;
const int C8 = 58;
const int D8 = 59;
const int E8 = 60;
const int F8 = 61;
const int G8 = 62;
const int H8 = 63;

const int NULL_SQUARE = 64;
const int NUM_SQUARES = 64;

// BITBOARD FILES

const U64 FILE_A = 0x0101010101010101ULL << 0;
const U64 FILE_B = 0x0101010101010101ULL << 1;
const U64 FILE_C = 0x0101010101010101ULL << 2;
const U64 FILE_D = 0x0101010101010101ULL << 3;
const U64 FILE_E = 0x0101010101010101ULL << 4;
const U64 FILE_F = 0x0101010101010101ULL << 5;
const U64 FILE_G = 0x0101010101010101ULL << 6;
const U64 FILE_H = 0x0101010101010101ULL << 7;

// BITBOARD ROWS

const U64 ROW_1 = 0xFFULL << (0 * 8);
const U64 ROW_2 = 0xFFULL << (1 * 8);
const U64 ROW_3 = 0xFFULL << (2 * 8);
const U64 ROW_4 = 0xFFULL << (3 * 8);
const U64 ROW_5 = 0xFFULL << (4 * 8);
const U64 ROW_6 = 0xFFULL << (5 * 8);
const U64 ROW_7 = 0xFFULL << (6 * 8);
const U64 ROW_8 = 0xFFULL << (7 * 8);

const U64 BOARD_LIMITS = FILE_H | ROW_8;

#endif /* CONSTANTS_H */
