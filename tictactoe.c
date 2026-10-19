#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void print_board(char tictactoe[7][13]);

int finished(char tictactoe[7][13]);

int real_row(int row);

int real_col(int col);

int player_v_computer(char tictactoe[7][13], char choice);

int player_v_player(char tictactoe[7][13]);

int main(void)
{
    printf("TIC-TAC-TOE!\n\n");

    char play_again;

    do {
        char tictactoe[7][13];

        for (int i = 0; i < 7; i++)
            for (int j = 0; j < 13; j++) {
                if (i == 2 || i == 4) {
                    if (j == 4 || j == 8)
                        tictactoe[i][j] = '|';
                    else
                        tictactoe[i][j] = '-';
                }
                else {
                    if (j == 4 || j == 8)
                        tictactoe[i][j] = '|';
                    else
                        tictactoe[i][j] = ' '; 
                }
            }

        print_board(tictactoe);
        printf("(board still empty)\n\n");

        int option;
        printf("[1] - PLAY AGAINST COMPUTER\n[2] - PLAY AGAINST A FRIEND\n");
        scanf("%d", &option);

        if (option == 1) {
            char choice;
            printf("Do you wanna play as X or O? ");
            scanf(" %c", &choice);
            
            int winner = player_v_computer(tictactoe, choice);
            if (winner == 1)
                printf("\n\nYOU WON!!!\n");
            else if (winner == 2)
                printf("\n\nThe computer has beaten you!\n");
            else
                printf("\n\nIT'S A DRAW!\n");
        }
        else {
            int winner = player_v_player(tictactoe);
            if (winner == 1)
                printf("\n\nX WINS!!!\n");
            else if (winner == 2)
                printf("\n\nO WINS!!!\n");
            else
                printf("\n\nIT'S A DRAW!\n");
        }

        printf("Do you wanna play again? (y/n) ");
        scanf(" %c", &play_again);
        printf("\n");
    } while (play_again == 'y' || play_again == 'Y');
    
    return 0;
}

void print_board(char tictactoe[7][13])
{
    int row_number = 1;
    printf("    1    2    3\n");
    for (int i = 0; i < 7; i++) {
        if (i == 1 || i == 3 || i == 5) {
            printf("%d  ", row_number);
            row_number++;
        }
        else
            printf("   ");
        for (int j = 0; j < 13; j++) 
            printf("%c", tictactoe[i][j]);
        
        printf("\n");
    }
}

int finished(char tictactoe[7][13])
{
    int x_row, x_col;
    int o_row, o_col;

    for (int i = 1; i <= 5; i += 2) {
        x_row = 0;
        for (int j = 2; j <= 10; j += 4) {
            if (tictactoe[i][j] == 'X') x_row++;

            if (x_row == 3) return 1;
        }
    }
    for (int j = 2; j <= 10; j += 4) {
        x_col = 0;
        for (int i = 1; i <= 5; i += 2) {
            if (tictactoe[i][j] == 'X') x_col++;

            if (x_col == 3) return 1;
        }
    }
    if (tictactoe[1][2] == tictactoe[3][6] && tictactoe[3][6] == tictactoe[5][10] && tictactoe[5][10] == 'X')
        return 1;
    if (tictactoe[1][10] == tictactoe[3][6] && tictactoe[3][6] == tictactoe[5][2] && tictactoe[5][2] == 'X')
        return 1;

    for (int i = 1; i <= 5; i += 2) {
        o_row = 0;
        for (int j = 2; j <= 10; j += 4) {
            if (tictactoe[i][j] == 'O') o_row++;

            if (o_row == 3) return 2;
        }
    }
    for (int j = 2; j <= 10; j += 4) {
        o_col = 0;
        for (int i = 1; i <= 5; i += 2) {
            if (tictactoe[i][j] == 'O') o_col++;

            if (o_col == 3) return 2; 
        }
    }
    if (tictactoe[1][2] == tictactoe[3][6] && tictactoe[3][6] == tictactoe[5][10] && tictactoe[5][10] == 'O')
        return 2;
    if (tictactoe[1][10] == tictactoe[3][6] && tictactoe[3][6] == tictactoe[5][2] && tictactoe[5][2] == 'O')
        return 2;

    return 0;
}

int real_row(int row)
{
    switch (row) {
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 5;
        default:
            return 0;
    }
}

int real_col(int col)
{
    switch (col) {
        case 1:
            return 2;
        case 2:
            return 6;
        case 3:
            return 10;
        default:
            return 0;
    } 
}

int player_v_computer(char tictactoe[7][13], char choice)
{
    srand(time(NULL));

    char player;
    char computer;
    int turn;

    if (choice == 'X' || choice == 'x') {
        player = 'X';
        computer = 'O';
        turn = 1;
    }
    else {
        player = 'O';
        computer = 'X';
        turn = 0;
    }

    for (int i = 0; i < 9; i++) {
        int ai_row, ai_col;
        bool again;

        if (turn % 2 == 0) {
            printf("\nCOMPUTER MOVE:\n");

            do {
                again = false;
                ai_row = real_row((rand() % 3) + 1);
                ai_col = real_col((rand() % 3) + 1);

                if (tictactoe[ai_row][ai_col] == 'X' || tictactoe[ai_row][ai_col] == 'O')
                    again = true;
            } while (again);

            tictactoe[ai_row][ai_col] = computer;
        }
        else {
            do {
                again = false;
                int row, col;

                printf("\nYour move, Player %c\n", player);

                printf("Select the row (1, 2, or 3): ");
                scanf("%d", &row);
                printf("Select the column (1, 2, or 3): ");
                scanf("%d", &col);
                
                row = real_row(row);
                col = real_col(col);

                if (row == 0 || col == 0) {
                    printf("THIS COORDINATE DOES NOT EXIST! Try again.\n");
                    again = true;
                }
                else if (tictactoe[row][col] != 'X' && tictactoe[row][col] != 'O')
                    tictactoe[row][col] = player;
                else {
                    printf("THIS POSITION IS OCCUPIED! Choose a different one.\n");
                    again = true;
                }
            } while (again);
        }

        print_board(tictactoe);

        int result = finished(tictactoe);
        if (result != 0) {
            if ((result == 1 && player == 'X') || (result == 2 && player == 'O'))
                return 1;
            else if ((result == 1 && computer == 'X') || (result == 2 && computer == 'O'))
                return 2;
        }

        turn++;
    }

    return 3;
}
  
int player_v_player(char tictactoe[7][13])
{
    int turn = 1;

    for (int i = 0; i < 9; i++) {
        bool again;

        do {
            int row, col;
            again = false;

            if (turn % 2 == 0) {
                printf("\nYour move, Player O\n");

                printf("Select the row (1, 2, or 3): ");
                scanf("%d", &row);
                printf("Select the column (1, 2, or 3): ");
                scanf("%d", &col);
                
                row = real_row(row);
                col = real_col(col);

                if (row == 0 || col == 0) {
                    printf("THIS COORDINATE DOES NOT EXIST! Try again.\n");
                    again = true;
                }
                else if (tictactoe[row][col] != 'X' && tictactoe[row][col] != 'O')
                    tictactoe[row][col] = 'O';
                else {
                    printf("THIS POSITION IS OCCUPIED! Choose a different one.\n");
                    again = true;
                }
            }
            else {
                printf("\nYour move, Player X\n");

                printf("Select the row (1, 2, or 3): ");
                scanf("%d", &row);
                printf("Select the column (1, 2, or 3): ");
                scanf("%d", &col);

                row = real_row(row);
                col = real_col(col);

                if (row == 0 || col == 0) {
                    printf("THIS COORDINATE DOES NOT EXIST! Try again.\n");
                    again = true;
                }
                else if (tictactoe[row][col] != 'X' && tictactoe[row][col] != 'O')
                    tictactoe[row][col] = 'X';
                else {
                    printf("THIS POSITION IS OCCUPIED! Choose a different one.\n");
                    again = true;
                }
            }
        } while (again);

        print_board(tictactoe);

        int result = finished(tictactoe);
        if (result != 0)
            return result;

        turn++;
    }

    return 3;
}
