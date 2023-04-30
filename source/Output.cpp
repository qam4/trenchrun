/*
 * File:   Output.cpp
 *
 */

#include "Output.h"

#include "MoveList.h"

#define MAX_ROW 6
#define MAX_COL 6

bool Output::colors_enabled { false };

string Output::board(const class Board board)
{
    stringstream ss;
    for (int row = MAX_ROW; row >= 0; row--)
    {
        ss << row + 1 << "  ";
        for (int col = 0; col <= MAX_COL; col++)
        {
            int square = (row * 8) + col;
            ss << Output::piece(board[square]) << " ";
        }
        ss << endl;
    }
    ss << endl;
    ss << "   A B C D E F G " << endl;
    ss << ((board.side_to_move() == WHITE) ? "WHITE" : "BLACK") << " turn" << endl;
    ss << "Ply: " << board.get_game_ply() << endl;
    // ss << "last_move_sideways=" << (int)board.last_move_sideways() << endl;
    return ss.str();
}

string Output::bitboard(U64 bb)
{
    stringstream ss;
    for (int row = MAX_ROW; row >= 0; row--)
    {
        ss << row + 1 << "  ";
        for (int col = 0; col <= MAX_COL; col++)
        {
            int square = (row * 8) + col;
            ss << (bb & (1ULL << square) ? 'X' : '-') << " ";
        }
        ss << endl;
    }
    ss << endl;
    ss << "   A B C D E F G " << endl;
    return ss.str();
}

string Output::piece(U8 piece)
{
    stringstream ss;
    if (Output::is_colors_enabled())
    {
        if (piece & BLACK)
        {
            ss << "\033[91m";  // Red
        }
        else if (piece)
        {
            ss << "\033[97m";  // White
        }
        ss << PIECE_CHARS[piece];
        ss << "\033[0m";
    }
    else
    {
        ss << PIECE_CHARS[piece];
    }

    return ss.str();
}

string Output::square(U8 square)
{
    const string ROWS = "12345678";
    const string FILES = "ABCDEFGH";
    stringstream ss;
    ss << FILES[square & 7] << ROWS[static_cast<size_t>(square >> 3)];
    return ss.str();
}

string Output::move(Move_t move, const class Board& board)
{
    (void)board;
    stringstream ss;

    U8 from = move_from(move);
    ss << Output::square(from);
    ss << Output::square(move_to(move));
    return ss.str();
}

string Output::move_fancy(Move_t move, const class Board& board)
{
    stringstream ss;

    U8 from = move_from(move);
    ss << Output::piece(board[from] & static_cast<U8>(~1));
    ss << Output::square(from);
    if (is_capture(move))
    {
        ss << 'x' << Output::piece(move_captured(move) & static_cast<U8>(~1));
    }
    ss << Output::square(move_to(move));
    ss << (((move_flags(move) & MOVED_SIDEWAYS) != 0) ? "-" : "");
    U16 score = move_score(move);
    if (score)
    {
        ss << "[" << score << "]";
    }
    return ss.str();
}

string Output::movelist(const class MoveList& list,
                        const class Board& board,
                        bool fancy = false,
                        bool choice = false)
{
    stringstream ss;
    if (list.length() == 0)
    {
        ss << "NO MOVES" << endl;
        return ss.str();
    }
    for (int i = 0; i < list.length(); i++)
    {
        if (i > 0)
        {
            ss << ", ";
            if (i % 8 == 0)
            {
                ss << endl;
            }
        }
        if (fancy)
        {
            ss << Output::move_fancy(list[i], board);
        }
        else
        {
            ss << Output::move(list[i], board);
            // ss << hex << list[i] << endl;
        }
        if (choice)
        {
            ss << " [" << i << "]";
        }
    }
    ss << endl;
    return ss.str();
}

string Output::board_with_movelist(const class MoveList& list, const class Board& board)
{
    stringstream ss;
    for (int row = MAX_ROW; row >= 0; row--)
    {
        ss << row + 1 << "  ";
        for (int col = 0; col <= MAX_COL; col++)
        {
            int square = (row * 8) + col;
            string piece = Output::piece(board[square]);

            for (int i = 0; i < list.length(); i++)
            {
                Move_t move = list[i];
                if (move_to(move) == square)
                {
                    piece = '.';
                    if (is_capture(move))
                    {
                        piece = 'C';
                    }
                }
            }
            ss << piece << " ";
        }
        ss << endl;
    }
    ss << endl;
    ss << "   A B C D E F G " << endl;
    ss << ((board.side_to_move() == WHITE) ? "WHITE" : "BLACK") << " turn" << endl;
    // ss << "last_move_sideways=" << (int)board.last_move_sideways() << endl;
    return ss.str();
}
