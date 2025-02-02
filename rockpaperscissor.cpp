#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Function to get the computer's move
char getComputerMove() {
    srand(time(NULL));
    int move = rand() % 3;
    if (move == 0) return 'p';
    else if (move == 1) return 's';
    return 'r';
}

// Function to return the result of the game
int getResults(char playerMove, char computerMove) {
    if (playerMove == computerMove) return 0; // Draw
    if ((playerMove == 's' && computerMove == 'p') ||
        (playerMove == 'p' && computerMove == 'r') ||
        (playerMove == 'r' && computerMove == 's')) {
        return 1; // Player wins
    }
    return -1; // Computer wins
}

// Function to display move name
string getMoveName(char move) {
    if (move == 'r') return "Rock";
    if (move == 'p') return "Paper";
    return "Scissors";
}

// Main function
int main() {
    char playerMove;

    cout << YELLOW << "\n\n\t\tWelcome to the Rock-Paper-Scissors Game! \n" << RESET;
    cout << CYAN << "\n\t\tEnter " << GREEN << "r" << CYAN << " for " << GREEN << "Rock" << CYAN
         << ", " << YELLOW << "p" << CYAN << " for " << YELLOW << "Paper" << CYAN
         << ", and " << MAGENTA << "s" << CYAN << " for " << MAGENTA << "Scissors.\n" << RESET;

    // Player input validation
    while (true) {
        cout << "\n\t\tYour move: ";
        cin >> playerMove;
        if (playerMove == 'p' || playerMove == 'r' || playerMove == 's') {
            break;
        } else {
            cout << RED << "\t\tInvalid move! Please enter r, p, or s.\n" << RESET;
        }
    }

    // Computer move
    char computerMove = getComputerMove();

    // Get result
    int result = getResults(playerMove, computerMove);

    // Display moves
    cout << BLUE << "\n\t\tYou chose: " << GREEN << getMoveName(playerMove) << RESET << endl;
    cout << RED << "\t\tComputer chose: " << YELLOW << getMoveName(computerMove) << RESET << endl;

    // Display result with colors
    if (result == 0) {
        cout << CYAN << "\n\t\tIt's a Draw! 🤝\n" << RESET;
    } else if (result == 1) {
        cout << GREEN << "\n\t\t🎉 Congratulations! You won! 🎉\n" << RESET;
    } else {
        cout << RED << "\n\t\tOh no! The computer won! 😢\n" << RESET;
    }

    cout << YELLOW << "\n\t\tThanks for playing! Play again anytime! \n" << RESET;

    return 0;
}
