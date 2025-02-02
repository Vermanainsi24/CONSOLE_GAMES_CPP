#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

const int width = 40;
const int height =20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], tailLen;
bool isGameOver;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

// Move cursor to a specific position (for smooth rendering)
void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Hide cursor to prevent blinking
void HideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 10;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Initialize the game
void InitGame() {
    isGameOver = false;
    dir = RIGHT; // Set initial movement to RIGHT so it's not static
    x = width / 2;
    y = height / 2;
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;
    score = 0;
    tailLen = 0;
    HideCursor();
}

// Render game board
void RenderGame(string playerName) {
    gotoxy(0, 0); // Move cursor to top-left (avoid flickering)
    cout << endl;cout << endl;cout << endl;
    // Draw top boundary
    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                cout << "|"; // Side walls
            else if (i == y && j == x)
                cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "*"; // Food
            else {
                bool printTail = false;
                for (int k = 0; k < tailLen; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        printTail = true;
                    }
                }
                if (!printTail) cout << " ";
            }
        }
        cout << endl;
    }

    // Draw bottom boundary
    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    // Display score
    cout << playerName << "'s Score: " << score << endl;
}

// Update game state (snake movement, collisions)
void UpdateGame() {
    int prevX = tailX[0], prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLen; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    // Check if the snake hits the wall
    if (x >= width || x <= 0 || y >= height || y <= 0)
        isGameOver = true;

    // Check if the snake hits its own tail
    for (int i = 0; i < tailLen; i++) {
        if (tailX[i] == x && tailY[i] == y)
            isGameOver = true;
    }

    // Check if the snake eats the food
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % (width - 2) + 1;
        fruitY = rand() % (height - 2) + 1;
        tailLen++;
    }
}

// Handle user input
void GetUserInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'x': isGameOver = true; break;
        }
    }
}

// Set difficulty level
int SetDifficulty() {
    int difficulty;
    char choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\n";
    cout << "Choose difficulty level: ";
    cin >> choice;
    switch (choice) {
        case '1': difficulty = 150; break;
        case '2': difficulty = 100; break;
        case '3': difficulty = 50; break;
        default: difficulty = 100;
    }
    return difficulty;
}

// Main function (Game loop)
int main() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    int speed = SetDifficulty();
    cout<<"W:Move UP\nS:Move DOWN\nA:Move LEFT\nD:Move RIGHT\nXExit the game";
    InitGame();
   

    while (!isGameOver) {
     



        RenderGame(playerName);
        GetUserInput();
        UpdateGame();
        Sleep(speed); // Control game speed
    }

    cout << "\nGame Over! " << playerName << ", your final score: " << score << endl;
    return 0;
}
