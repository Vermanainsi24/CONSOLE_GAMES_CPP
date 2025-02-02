#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <map>
#include <limits>

using namespace std;

#define MAX_ATTEMPTS 6
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"

class HangmanGame {
public:
    HangmanGame() {
        srand(static_cast<unsigned int>(time(nullptr)));
        loadWords();
        resetGame();
    }

    void play() {
        char choice;
        do {
            resetGame();
            startGame();
            cout << CYAN << "Do you want to play again? (y/n): " << RESET;
            cin >> choice;
        } while (tolower(choice) == 'y');
        cout << GREEN << "Thanks for playing Hangman! Goodbye!" << RESET << endl;
    }

private:
    string secretWord, category, hint;
    string currentWord;
    int attemptsLeft;
    vector<char> guessedLetters;
    int score;
    map<string, vector<pair<string, string>>> wordPool;

    void loadWords() {
        wordPool["Fruits"] = {{"apple", "A red or green fruit"}, {"banana", "A long yellow fruit"}, {"grape", "Small purple or green fruit"},
                              {"mango", "King of fruits"}, {"cherry", "A small red fruit"}};
        wordPool["Animals"] = {{"tiger", "A big striped cat"}, {"elephant", "Largest land animal"}, {"giraffe", "Tallest land animal"},
                               {"panda", "Loves bamboo"}, {"dolphin", "Smart marine mammal"}};
    }

    void resetGame() {
        int catIndex = rand() % wordPool.size();
        auto it = wordPool.begin();
        advance(it, catIndex);
        category = it->first;
        int wordIndex = rand() % it->second.size();
        secretWord = it->second[wordIndex].first;
        hint = it->second[wordIndex].second;
        currentWord = string(secretWord.length(), '_');
        attemptsLeft = MAX_ATTEMPTS;
        guessedLetters.clear();
        score = 0;
    }

    void startGame() {
        cout << GREEN << "Welcome to Hangman!" << RESET << endl;
        cout << "Category: " << BLUE << category << RESET << endl;
        cout << "You have " << attemptsLeft << " attempts." << endl;

        while (attemptsLeft > 0) {
            displayGameInfo();
            char guess;
            cout << CYAN << "Guess a letter (or type '?' for a hint): " << RESET;
            cin >> guess;

            if (guess == '?') {
                giveHint();
                continue;
            }

            if (!isalpha(guess)) {
                cout << RED << "Invalid input! Enter a letter." << RESET << endl;
                continue;
            }

            guess = tolower(guess);
            if (alreadyGuessed(guess)) {
                cout << YELLOW << "You've already guessed that letter." << RESET << endl;
            } else {
                processGuess(guess);
            }
        }

        if (attemptsLeft == 0) {
            cout << RED << "Game Over! The word was: " << secretWord << RESET << endl;
        }
    }

    bool alreadyGuessed(char letter) {
        return find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end();
    }

    void processGuess(char letter) {
        bool correctGuess = false;
        for (size_t i = 0; i < secretWord.length(); i++) {
            if (secretWord[i] == letter) {
                currentWord[i] = letter;
                correctGuess = true;
            }
        }
        guessedLetters.push_back(letter);
        if (correctGuess) {
            score += 10;
            cout << GREEN << "Correct!" << RESET << endl;
            if (currentWord == secretWord) {
                displayGameInfo();
                cout << GREEN << "Congratulations! You guessed the word: " << secretWord << " with score: " << score << RESET << endl;
                attemptsLeft = 0;
            }
        } else {
            cout << RED << "Wrong guess!" << RESET << endl;
            attemptsLeft--;
            drawHangman();
        }
    }

    void giveHint() {
        cout << YELLOW << "Hint: " << hint << RESET << endl;
        score -= 5;
    }

    void displayGameInfo() {
        cout << "Word: " << currentWord << endl;
        cout << "Attempts left: " << attemptsLeft << endl;
        cout << "Guessed letters: ";
        for (char letter : guessedLetters) cout << letter << " ";
        cout << endl;
    }

    void drawHangman() {
        vector<string> hangman = {
            "_____\n  |     |\n  |\n  |\n  |\n  |\n  |",
            "   _____\n  |     |\n  |     O\n  |\n  |\n  |\n  |",
             "   _____\n  |     |\n  |     O\n  |     |\n  |\n  |\n  |",
              "   _____\n  |     |\n  |     O\n  |    /|\n  |\n  |\n  |",
               "   _____\n  |     |\n  |     O\n  |    /|\\\n  |\n  |\n  |",
               "   _____\n  |     |\n  |     O\n  |    /|\\\n  |    /\n  |\n  |",
            "   _____\n  |     |\n  |     O\n  |    /|\\\n  |    / \\\n  |\n  |",
            
            };
        cout << RED << hangman[MAX_ATTEMPTS - attemptsLeft] << RESET << endl;
    }
};

int main() {
    HangmanGame game;
    game.play();
    return 0;
}