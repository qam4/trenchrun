/*
 * File:   Trenchrun.cpp
 *
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"
#include "Output.h"
#include "Parser.h"

using namespace std;
#define SEARCH_DEPTH 64

static void print_help(void);

int main()
{
    bool computer_plays[2] = { false };

    string fen = "++++++++/1TT1TT1+/2~*~2+/XX3XX+/7+/xx3xx+/2+@+2+/1tt1tt1+";
    Board board = Parser::parse_fen(fen);

    while (true)
    {
        cout << Output::board(board);
        if (board.is_game_over())
        {
            if (board.side_to_move() == WHITE)
            {
                cout << "Black player won" << endl;
            }
            else
            {
                cout << "White player won" << endl;
            }
            break;
        }

        if (computer_plays[board.side_to_move()])
        {
            clock_t tic = clock();
            cout << "Thinking..." << endl;

            Move_t move;
            move = board.search(SEARCH_DEPTH);
            clock_t toc = clock();
            double elapsed_secs = double(toc - tic) / CLOCKS_PER_SEC;
            cout << "time: " << elapsed_secs << "s" << endl;
            cout << "searched moves: " << board.get_searched_moves() << endl;
            cout << "searched moves per second: " << int(board.get_searched_moves() / elapsed_secs)
                 << endl;

            cout << "Computer move: " << Output::move_fancy(move, board) << endl;
            board.do_move(move);
            continue;
        }

        string line;
        cout << "> ";
        getline(cin, line);

        if (line == "quit")
        {
            break;
        }
        else if (line == "help")
        {
            print_help();
        }
        else if (line.rfind("move ", 0) == 0)
        {
            Move_t move = Parser::move(line.substr(5), board);
            if (is_valid_move(move, board))
            {
                board.do_move(move);
            }
        }
        else if (line.rfind("play ", 0) == 0)
        {
            if (line.rfind("white", 5) == 5)
            {
                computer_plays[WHITE] = true;
                cout << "Computer plays white" << endl;
            }
            else if (line.rfind("black", 5) == 5)
            {
                computer_plays[BLACK] = true;
                cout << "Computer plays black" << endl;
            }
            else
            {
                cout << "<color> should be black or white" << endl;
            }
        }
    }
    cout << "Goodbye." << endl;
}

void print_help()
{
    cout << "Commands:\n"
            "  quit                      Exit this program\n"
            "  help                      Display this screen\n"
            "  move <move>               Play <move> on the board\n"
            "  play <color>              Let computer play <color>\n";
}
