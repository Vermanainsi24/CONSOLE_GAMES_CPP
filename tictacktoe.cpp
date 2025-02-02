#include <iostream>
#include <limits>
using namespace std;

// ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

// Function to draw the board
void drawBoard(char board[3][3]) {
    cout << CYAN << "\n  1 | 2 | 3" << RESET << endl;
    cout << " ---+---+---" << endl;
    cout << CYAN << "  4 | 5 | 6" << RESET << endl;
    cout << " ---+---+---" << endl;
    cout << CYAN << "  7 | 8 | 9" << RESET << endl;
    cout << "\nCurrent Board:\n";
    for (int i = 0; i < 3; i++) {
        cout << "  ";
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X') {
                cout << RED << board[i][j] << RESET;
            } else if (board[i][j] == 'O') {
                cout << GREEN << board[i][j] << RESET;
            } else {
                cout << board[i][j];
            }
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << " ---+---+---\n";
    }
    cout << "\n";
}

// Function to check for a win
bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return true;
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return true;
    return false;
}

// Function to reset the board
void resetBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Main game function
void playGame() {
    char board[3][3];
    resetBoard(board);
    char player = 'X';
    int move;

    cout << BOLD << YELLOW << "Welcome to Interactive Tic-Tac-Toe!" << RESET << "\n";
    drawBoard(board);

    for (int turn = 0; turn < 9; turn++) {
        while (true) {
            cout << "Player " << (player == 'X' ? RED : GREEN) << player << RESET << "'s turn. Enter a position (1-9): ";
            cin >> move;
            
            if (cin.fail() || move < 1 || move > 9) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number between 1 and 9.\n";
                continue;
            }
            
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;
            
            if (board[row][col] != ' ') {
                cout << "That position is already taken. Try again!\n";
            } else {
                board[row][col] = player;
                break;
            }
        }

        drawBoard(board);

        if (checkWin(board, player)) {
            cout << BOLD << "Congratulations! Player " << (player == 'X' ? RED : GREEN) << player << RESET << " wins!\n";
            return;
        }

        player = (player == 'X') ? 'O' : 'X';
    }
    cout << BOLD << "It's a draw!\n" << RESET;
}

int main() {
    char playAgain;
    do {
        playGame();
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
    cout << BOLD << CYAN << "Thanks for playing! Goodbye!" << RESET << endl;
    return 0;
}
