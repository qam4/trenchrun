# trenchrun

This is the trenchrun project.

# Building and installing

See the [BUILDING](BUILDING.md) document.

# Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.

# Licensing

<!--
Please go to https://choosealicense.com/licenses/ and choose a license that
fits your needs. The recommended license for a project of this type is the
GNU AGPLv3.
-->


********  TWO PLAYER GAMES - "Trench Run" ********

"Star Wars" is back!  Not only with the latest blockbuster "The Force Awakens",
but also with this year's brand new two-player board game "Trench Run".  It's
a chess-like game designed just for you!  "Trench Run" is based on the climatic
aerial battle at the end of the first 1977 Star Wars movie, where the rebel
ships had to maneuver down a narrow trench in order to destroy the Death Star.

You will each write a program that can play "Trench Run" against a human
opponent. The game and the program requirements are detailed below.


THE GAME

"Trench Run" is a chess-like game in which each player takes turns moving one
of his/her pieces, and tries to capture the opponent's Death Star.  It is
played on an 7x7 board, and each side starts with a set of pieces consisting
of 1 Death Star, 2 walls, 4 tie fighters, and 4 x-wings.  The different pieces
have rules about how they can move, which is described later.

Players alternate moves, moving one of their own pieces each turn.
When it is your turn, you MUST make a move -- you cannot pass.
If it is your turn and you have no legal moves, you lose.

A player wins either when he/she captures the opponents' Death Star,
or if it is his/her opponent's turn but the opponent has no legal moves.

The initial position is:

     - T T - T T -  (COMPUTER)
     - - ~ * ~ - -
     X X - - - X X
     - - - - - - -
     x x - - - x x
     - - + @ + - -
     - t t - t t -  (HUMAN)

   T,X,~,* are the computer's tie fighters, x-wings, walls, and death star
      (moving DOWN the board).

   t,x,+,@ are the human's tie fighters, x-wings, walls, and death star
      (moving UP the board).

The pieces move as follows:

X-WING
-- moves roughly the same as the "bishop" in regular chess.
    That is, diagonally in one direction any number of squares.
-- may move either onto an empty square, or onto a square occupied by another
    piece (thus capturing it).
-- CANNOT jump over other pieces.  Once it bumps into a piece
    or captures a piece, that is as far as it can go.
-- an x-wing can move or capture in the forward direction.
    It can only move in the backwards direction if that move is a capture.

TIE-FIGHTER
-- moves roughly the same as a "rook" in regular chess.
    That is, horizontally or vertically in one direction any number of squares.
-- may move either onto an empty square, or onto a square occupied by another
    piece (thus capturing it).
-- CANNOT jump over other pieces.  Once it bumps into a piece
    or captures a piece, that is as far as it can go.
-- a tie-fighter can move or capture in the forward or sideways direction.
    It can only move in the backwards direction if that move is a capture.
-- players are not allowed to make a sideways tie-fighter move on two successive
    moves.  That is, if you move one of your tie-fighters sideways, you are not
    allowed to move ANY of your tie-fighters sideways on the next move.

DEATH STAR
-- cannot move.
-- if it is captured, you lose!
-- can only be captured by a piece moving backwards.

WALLS
-- cannot move.
-- cannot be captured.
-- since the death star can only be captured by a piece moving backwards,
    capturing the death star requires maneuvering a piece through the
    "trench" against the back row, behind the walls.

OTHER DETAILS -

-- moving is compulsory.  That is, a player cannot "pass".
-- you are never allowed to capture your own piece.  That is an illegal move.
-- however, it is not illegal to leave your death star in danger.  If the
     opponent doesn't see that he/she can capture the death star, you play on!
-- unlike chess, there is no such thing as "check" or "checkmate".  Winning
     is by actually capturing the death star (or the opponent having no move).
-- unlike chess, there are no pawns or knights or queens.
-- unlike chess, inability to move isn't a stalemate draw - it is a LOSS.
-- unlike checkers, capturing isn't compulsory.
-- unlike Go (Weiqi), players don't place pieces on the board.
    The pieces are on the board at the beginning, and are moved or captured.

THE PROGRAM

Your program is one player, and will attempt to defeat the human operator.
It must fulfill the following requirements:

1. It first asks the human whether he/she wants to move first or second.

2. The current position is displayed on the screen before and after each
   move, with the axes labeled as in the following example:

   7  - T T - T - T  COMPUTER
   6  X - ~ * ~ - -
   5  X - - - - X X
   4  - - x - - - -
   3  x - - - - x x
   2  - - + @ + - -
   1  t - t - t t -  HUMAN

      A B C D E F G

   You are encouraged to make minor modifications to the display if you think
   it is easier to see (or more fun) with different characters for the pieces.
   If you want to make a graphical user interface, that's even better (although
   you won't get extra credit for it).  But whatever you do, the axes MUST be
   labeled, with row numbers and column letters, EXACTLY in the above manner.

   (If, like me, you use simple "ascii" output to System.out, as shown above, you
    will probably find it a LOT easier to see the position if you use different
    colors for the human's pieces versus the computer's pieces.  This is actually
    very easy to do in C++ with ansi escape sequences, and your instructor will
    post the relevant code.  You are encouraged to add it to your program's display,
    although it isn't required.)

3. The human enters moves using the notation above, for the FROM square
   followed by the TO square.  For instance, in the position above, the
   human could use the x-wing on C4 to capture the computer's x-wing on A6
   and the move would be entered as follows: C4A6 (no spaces).  Of course,
   capturing is not compulsory, so there are many other possible legal moves,
   such as G3E5, C4D5, or F1G1 (presuming that the human hadn't made some
   horizontal tie-fighter move such as B1A1 on the previous turn), etc.

4. When your program makes a move, it must print out the move using the same
   notation described in #3 above, AND display the new position.  When printing out
   the computer's move, don't "flip" the axes - for example, in the above position,
   if the computer moves its tie fighter in the upper right, the move should be
   displayed as G7F7, that is, using exactly the same notation and the same axis labels.

5. The program must detect when the game has ended, i.e. when a death star has
   has been captured, or if a player has no legal moves and has thus lost.
   It should correctly announce when it has won, and should also correctly
   announce when the human has won.

6. The program must never play an illegal move.

7. The program should detect when an illegal move has been entered
   and require the human to re-enter a valid move.

8. At each turn, the program must make its move in 5 seconds or less.

9. The program should be sufficiently bug-free to play through an entire
   game without ever crashing.  Memory-leaks can cause these kinds
   of programs to fail late in the game, so test your program on several
   complete games, to be sure it is reliable through a whole game.

10. Your program must run on a CAMPUS workstation.  For the tournament,
   you MUST run on a campus workstation, not your own.  It could be one of
   the computers in 5029, or by connecting into one of the ECS servers.
   This is to make sure that everyone in the class has equal access to
   computing power.  If you have unique requirements, such as a wanting to
   use a language that isn't currently on a campus workstation, please
   make arrangements with me well ahead of the due date.


STRATEGY AND OTHER REQUIREMENTS

1. To get FULL credit, your program must satisfy the requirements listed
   above, and also MUST correctly use minimax search, at least 5 plies deep,
   with alpha-beta pruning (correctly), to determine the computer's moves.
   Refrain from trying to find a simple closed-form solution to the game,
   as that would defeat the purpose of the assignment.

2. You can use any programming language you want.  Any compiled language
   that generates efficient code, such as C or C++ are good choices.
   You can also use Java, C#, Python, Ruby, Perl, BASIC, Smalltalk, Scheme,
   LISP, Clojure, or other interpreted languages, but don't be surprised if
   your code searches 1 or 2 plies less than those written in C or C++.
   If you want to use a language other than one of the ones mentioned
   here, please see me first.

3. You can decide whether you want to do a deep selective search, or a
   more shallow but exhaustive (full-width) search.  Most programs like
   this perform better with exhaustive search, because a selective search
   would require an excellent heuristic to choose which moves to discard
   -- otherwise it would risk failing to consider important possibilities.
   You are strongly encouraged to use full-width search as described in class
   and in your textbook.


TOURNAMENT

After the due date, we will have a "fun" tournament, in which your programs
will play against each other.  This will give us a chance to compare the
various strategies we used.  The tournament will be much more fun if you come
up with a name for your program.  In fact, that is a requirement!  Your instructor
has already finished his program, and has named it "TARKIN", in reference to one
of the villains in the first Star Wars movie.  TARKIN is pretty strong, but beatable.

Submit your solution (the code) to your instructor using SacCT.  The code
should be included in a ZIP file, along with a 2-3 page document describing
each the following:

      a. your program's NAME
      b. instructions on how to install, run, and play against your program
      c. what language it is written in
      d. which techniques you used (alpha-beta, iterative deepening, history tables, etc.)
      e. how deep it typically searches (how many plies), from the opening position,
          and then later in the game
      f. a brief explanation of the factors your program considers in its
          terminal evaluation function
      g. how strong you think it is -
          - be specific (can it beat you?  has it played any of the other programs?)
      h. anything unusual or unique about your program
      i. any bugs you are aware of that cause it to crash or make illegal moves?
      j. any bugs you are aware of that cause it to sometimes make weak moves?

As the date of the tournament gets closer, your instructor will provide
another handout with some very minor additional requirements that will help
make the tournament run smoothly.

-----
