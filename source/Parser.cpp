/*
 * File:   Parser.cpp
 *
 */

#include "Parser.h"

class Board Parser::parse_fen(string fen)
{
    Board board = Board();

    size_t len = fen.length();

    size_t pos = 0;  // position in string
    //[not used]int square = A1;

    // 8 rows of pieces
    for (int row = 7; row >= 0; row--)
    {
        while (fen[pos] == '/')
            pos++;
        for (int col = 0; col < 8; col++)
        {
            char c = fen[pos++];
            // cout << "[" << row<< "," << col << "]=" << c << endl;
            //  if number skip ahead that many columns
            if (c >= '1' && c <= '8')
            {
                col += c - '1';
            }
            else
            {  // find piece
                U8 piece = parse_piece(c);
                if (piece)
                    board.add_piece(piece, (row * 8) + col);
            }
        }
    }
    while (fen[pos] != ' ')
        if (pos++ >= len)
            return board;
    while (fen[pos] == ' ')
        if (pos++ >= len)
            return board;

    // side to move
    U8 side_to_move = Parser::side(fen[pos++]);
    board.set_side_to_move(side_to_move);

    if (pos++ >= len)
        return board;
    while (fen[pos] == ' ')
        if (pos++ >= len)
            return board;

    // last move sideways
    U8 last_move_sideways = NO_MOVED_SIDEWAYS;
    while (fen[pos] != ' ')
    {
        // cout << "fen:msw=" << fen[pos] << endl;
        last_move_sideways = last_move_sideways | Parser::last_move_sideways(fen[pos]);
        board.set_last_move_sideways(last_move_sideways);
        if (pos++ >= len)
            return board;
    }

    while (fen[pos] == ' ')
        if (pos++ >= len)
            return board;

    // full-move-count
    int full_move_count = 0;
    while (fen[pos] != ' ')
    {
        full_move_count = full_move_count * 10 + (fen[pos] - '0');
        if (pos++ >= len)
            return board;
    }

    return board;
}

U8 Parser::parse_piece(char piece)
{
    for (U8 i = 2; i < 14; i++)
    {
        if (PIECE_CHARS[i] == piece)
            return i;
    }
    return EMPTY;
}

U8 Parser::side(char c)
{
    if (c == 'b' || c == 'B')
        return BLACK;
    return WHITE;
}

U8 Parser::last_move_sideways(char c)
{
    if (c == 'b' || c == 'B')
        return BLACK_MOVED_SIDEWAYS;
    if (c == 'w' || c == 'W')
        return WHITE_MOVED_SIDEWAYS;
    return NO_MOVED_SIDEWAYS;
}

U8 Parser::square(char sq[])
{
    if ((sq[0] < 'A') || (sq[0] > 'G'))
        return NULL_SQUARE;
    if ((sq[1] < '1') || (sq[1] > '7'))
        return NULL_SQUARE;

    int col = sq[0] - 'A';
    int row = sq[1] - '1';
    return static_cast<U8>((row * 8) + col);
}

U32 Parser::move(string str, Board& board)
{
    size_t len = str.length();
    U8 from, to, piece, capture;
    U32 move = 0;

    // note: is it ok to return 0 for errors?
    if (len != 4)
        return 0;

    from = square(&str[0]);
    to = square(&str[2]);
    piece = board[from];
    capture = board[to];
    if ((from == NULL_SQUARE) || (to == NULL_SQUARE))
        return 0;
    U8 flags = NO_FLAGS | board.last_move_sideways();
    // Check if tie-fighter sideway move
    // cout << "piece=" << ((piece&(~1)) == TIEFIGHTER)
    // << ((to&(~C64(0x7))) == (from&(~C64(0x7))))
    // << ", from=" << (int)from << "-" << (int)(from&(~C64(0x7)))
    // << ", to=" << (int)to << "-" << (int)(to&(~C64(0x7))) << endl;
    if (((piece & (~1)) == TIEFIGHTER) && ((to & (~C64(0x7))) == (from & (~C64(0x7)))))
    {
        // cout << "this is a move sideways"  << endl;
        flags |= MOVED_SIDEWAYS;
    }
    move |= build_move_all(from, to, flags, capture);
    // cout << "move=" << hex<<move << endl;
    return move;
}
