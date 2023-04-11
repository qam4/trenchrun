/*
 * File:   main.cpp
 *
 */

#include <cstdlib>
#include <ctime>

#include "Board.h"
#include "MoveGenerator.h"
#include "MoveList.h"
#include "Output.h"
#include "Parser.h"

using namespace std;
#define SEARCH_DEPTH 6

/*
 *
 */
int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    // static_assert(1ULL << 2 == 0ULL);
    // cout << ((U32)(-5)) % 64 << endl;
    // cout << Output::bitboard(1ULL << 33) << endl;
    // MoveGenerator::generate_move_lookup_tables();

    char type;
    do
    {
        cout << "Do you want to play first? [y/n]" << endl;
        cin >> type;
    } while (!cin.fail() && type != 'y' && type != 'n');

    if (type == 'y')
    {
        // human plays first
        string fen = "++++++++/1TT1TT1+/2~*~2+/XX3XX+/7+/xx3xx+/2+@+2+/1tt1tt1+";
        Board board = Parser::parse_fen(fen);
        cout << Output::board(board);

        do
        {
            // Human's turn
            if (board.is_game_over())
                break;
            MoveList list;
            MoveGenerator::add_all_moves(list, board, board.side_to_move());
            cout << dec << list.length() << " available moves:" << endl;
            cout << Output::movelist(list, board, false, true);

            assert(list.contains_valid_moves(board));
            assert(!list.contains_duplicates());

            string input;
            Move_t move;
            do
            {
                cout << "your move: ";
                int number;
                std::cin >> number;

                move = list[number];  // Parser::move(input, board);
            } while (!is_valid_move(move, board));
            board.do_move(move);
            cout << Output::board(board);

            // Computer's turn
            if (board.is_game_over())
                break;
            clock_t tic = clock();
            cout << "Thinking..." << endl;
            // move = board.minimax_root(SEARCH_DEPTH, false); // Computer is BLACK, trying to
            // minimize move = board.negamax_root(SEARCH_DEPTH);
            move = board.alphabeta_root(SEARCH_DEPTH);
            clock_t toc = clock();
            double elapsed_secs = double(toc - tic) / CLOCKS_PER_SEC;
            cout << "time: " << elapsed_secs << "s" << endl;
            cout << "searched moves: " << board.get_searched_moves() << endl;

            cout << "Computer move: " << Output::move_fancy(move, board) << endl;
            board.do_move(move);
            cout << Output::board(board);
        } while (1);
        if (board.side_to_move() == WHITE)
        {
            cout << "Black player won" << endl;
        }
        else
        {
            cout << "White player won" << endl;
        }
    }

    return 0;
}
