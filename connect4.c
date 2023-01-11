#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// make_move(board, column, player) updates the board following a move
//   by the given player in the given column; returns false if the move
//   was illegal because the column was full
// requires: 0 <= column < 7
//           player is either 'X' or 'O'
bool make_move(char board[6][7], int column, char player);

// check_win(board) returns true if the given player has 4 connected
//   pieces on the board
bool check_win(char board[6][7], char player);

// test_check_win() tests the make_move function using assert; if an error is
//   detected then the program stops
void test_check_win(void);

// test_make_move() tests the check_win function using assert; if an error is
//   detected then the program stops
void test_make_move(void);

int main(void)
{
    char playerA = 'X';
    char playerB = 'O';
    char board[6][7] = {{'.', '.', '.', '.', '.', '.', '.'},
                        {'.', '.', '.', '.', '.', '.', '.'},
                        {'.', '.', '.', '.', '.', '.', '.'},
                        {'.', '.', '.', '.', '.', '.', '.'},
                        {'.', '.', '.', '.', '.', '.', '.'},
                        {'.', '.', '.', '.', '.', '.', '.'}};

    int column;
    bool move;
    int i;

    test_check_win();
    test_make_move();

    printf("\nWelcome to Connect-4! Here is some information you might need, player A is 'X' and player B is 'O'. You have to type the column number (0 to 6) to play the game. Hope you enjoy!\n");

    for (i = 0; i < 42; i++) // There can only be 42 turns maximum to finish the game.
    {
        if (i % 2 == 0) // Dividing the loop alternately between 2 players.
        {
            printf("Enter the column number: ");
            scanf("%d", &column);

            if (column >= 0 && column <= 6) // Checking if the value of column is correct.
            {
                move = make_move(board, column, playerA);

                if (move == false) // Checking if move is illegal.
                {
                    printf("Illegal move, try again!\n");
                    i--;
                }

                if (check_win(board, playerA) == true) // Checking the win
                {
                    for (int i = 0; i < 6; i++) // Printing the winning board
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            printf("%c ", board[i][j]);
                        }
                        printf("\n");
                    }
                    printf("PlayerA wins!\n");
                    break;
                }
            }
            else // If the value of column is not correct
            {
                printf("Illegal move, try again!\n");
                i--;
            }
        }
        else // Dividing the loop alternately between 2 players.
        {
            printf("Enter the column number: ");
            scanf("%d", &column);

            if (column >= 0 && column <= 6) // Checking if the value of column is correct.
            {
                move = make_move(board, column, playerB);

                if (move == false) // Checking if move is illegal.
                {
                    printf("Illegal move, try again!\n");
                    i--;
                }

                if (check_win(board, playerB) == true) // Checking the win
                {
                    for (int i = 0; i < 6; i++) // Printing the winning board
                    {
                        for (int j = 0; j < 7; j++)
                        {
                            printf("%c ", board[i][j]);
                        }
                        printf("\n");
                    }
                    printf("PlayerB wins!\n");
                    break;
                }
            }
            else // If the value of column is not correct
            {
                printf("Illegal move, try again!\n");
                i--;
            }
        }

        for (int i = 0; i < 6; i++) // Printing the board for every new move.
        {
            for (int j = 0; j < 7; j++)
            {
                printf("%c ", board[i][j]);
            }
            printf("\n");
        }
    }

    if (i >= 42) // If the game doesn't end after 42 turns, it is a tie!
    {
        printf("It is a tie!\n");
    }
}

// MAKE MOVE
bool make_move(char board[6][7], int column, char player)
{
    for (int i = 5; i >= 0; i--)
    {
        if (board[i][column] != 'X' && board[i][column] != 'O') // Checking if the space is free or not
        {
            board[i][column] = player;
            return true;
        }
    }
    return false;
}

// CHECK WIN
bool check_win(char board[6][7], char player)
{
    int count = 0;

    // Vertical
    for (int i = 0; i < 7; i++)
    {
        count = 0;
        for (int j = 0; j < 6; j++)
        {
            if (board[j][i] == player)
            {
                count++;
                if (count == 4)
                {
                    return true;
                }
            }
            else
            {
                count = 0;
            }
        }
    }

    // Horizontal
    for (int i = 0; i < 6; i++)
    {
        count = 0;
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == player)
            {
                count++;
                if (count == 4)
                {
                    return true;
                }
            }
            else
            {
                count = 0;
            }
        }
    }

    // Diagonal
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            count = 0;
            for (int k = 0; k < 6; k++)
            {
                if (board[i + k][j + k] == player && (i + k) < 6 && (j + k) < 7)
                {
                    count++;
                    if (count == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

    // Back Diagonal
    for (int i = 5; i >= 0; i--)
    {
        for (int j = 0; j < 7; j++)
        {
            count = 0;
            for (int k = 0; k < 6; k++)
            {
                if (board[i - k][j + k] == player && (i - k) >= 0 && (j + k) < 7)
                {
                    count++;
                    if (count == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    count = 0;
                }
            }
        }
    }

    return false;
}

// TEST CHECK WIN
void test_check_win(void)
{
    char player = 'X';
    // When win is false
    char board1[6][7] = {{'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'}};

    assert(check_win(board1, player) == false);
    // Vertical win
    char board2[6][7] = {{'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', 'X', '.', '.', '.', '.', '.'},
                         {'.', 'X', '.', '.', '.', '.', '.'},
                         {'.', 'X', '.', '.', '.', '.', '.'},
                         {'.', 'X', '.', '.', '.', '.', '.'}};

    assert(check_win(board2, player) == true);
    // Horizontal win
    char board3[6][7] = {{'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'X', 'X', 'X', 'X', 'X', '.', '.'}};

    assert(check_win(board3, player) == true);
    // Back Diagonal win
    char board4[6][7] = {{'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', 'X'},
                         {'.', '.', '.', '.', '.', 'X', '.'},
                         {'.', '.', '.', '.', 'X', '.', '.'},
                         {'.', '.', '.', 'X', '.', '.', '.'}};

    assert(check_win(board4, player) == true);
    // Diagonal win
    char board5[6][7] = {{'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'X', '.', '.', '.', '.', '.', '.'},
                         {'.', 'X', '.', '.', '.', '.', '.'},
                         {'.', '.', 'X', '.', '.', '.', '.'},
                         {'.', '.', '.', 'X', '.', '.', '.'}};

    assert(check_win(board5, player) == true);
}

// TEST MAKE MOVE
void test_make_move(void)
{
    char board1[6][7] = {{'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'},
                         {'.', '.', '.', '.', '.', '.', '.'}};

    int column = 3;
    char player = 'X';

    assert(make_move(board1, column, player) == true);
    assert(board1[5][3] == 'X');

    assert(make_move(board1, column, player) == true);
    assert(board1[4][3] == 'X');

    char board2[6][7] = {{'.', '.', '.', 'O', '.', '.', '.'},
                         {'.', '.', '.', 'X', '.', '.', '.'},
                         {'.', '.', '.', 'O', '.', '.', '.'},
                         {'.', '.', '.', 'X', '.', '.', '.'},
                         {'.', '.', '.', 'O', '.', '.', '.'},
                         {'.', '.', '.', 'X', '.', '.', '.'}};
    assert(make_move(board2, column, player) == false); // When the column is full
}
