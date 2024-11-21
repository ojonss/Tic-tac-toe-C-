#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void displayBoard() {
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
    cout << "---|---|---" << endl;
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;
}

bool checkWin() {
    const int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}             // Diagonals
    };
    for (auto &pattern : winPatterns) {
        if (board[pattern[0]] == board[pattern[1]] && board[pattern[1]] == board[pattern[2]]) {
            return true;
        }
    }
    return false;
}

bool checkDraw() {
    for (char cell : board) {
        if (cell != 'X' && cell != 'O') {
            return false;
        }
    }
    return true;
}

void playerMove(char player) {
    int move;
    while (true) {
        cout << "Player " << player << ", enter your move (1-9): ";
        cin >> move;
        if (move >= 1 && move <= 9 && board[move - 1] != 'X' && board[move - 1] != 'O') {
            board[move - 1] = player;
            break;
        } else {
            cout << "Invalid move. Try again." << endl;
        }
    }
}

void aiMove() {
    srand(time(0));
    int move;
    while (true) {
        move = rand() % 9;
        if (board[move] != 'X' && board[move] != 'O') {
            board[move] = 'O';
            break;
        }
    }
}

int main() {
    char currentPlayer = 'X';
    bool playAgainstAI;
    cout << "Do you want to play against the AI? (1 for Yes, 0 for No): ";
    cin >> playAgainstAI;

    while (true) {
        displayBoard();
        if (currentPlayer == 'X' || !playAgainstAI) {
            playerMove(currentPlayer);
        } else {
            aiMove();
        }
        if (checkWin()) {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }
        if (checkDraw()) {
            displayBoard();
            cout << "It's a draw!" << endl;
            break;
        }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
    return 0;
}