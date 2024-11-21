#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

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

int minimax(vector<char> board, bool isMaximizing) {
    if (checkWin()) {
        return isMaximizing ? -1 : 1;
    }
    if (checkDraw()) {
        return 0;
    }

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 9; ++i) {
            if (board[i] != 'X' && board[i] != 'O') {
                char temp = board[i];
                board[i] = 'O';
                int score = minimax(board, false);
                board[i] = temp;
                bestScore = max(score, bestScore);
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 9; ++i) {
            if (board[i] != 'X' && board[i] != 'O') {
                char temp = board[i];
                board[i] = 'X';
                int score = minimax(board, true);
                board[i] = temp;
                bestScore = min(score, bestScore);
            }
        }
        return bestScore;
    }
}

void minimaxAiMove() {
    int bestMove = -1;
    int bestScore = numeric_limits<int>::min();
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            char temp = board[i];
            board[i] = 'O';
            int score = minimax(board, false);
            board[i] = temp;
            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    board[bestMove] = 'O';
}

int main() {
    char currentPlayer = 'X';
    int gameMode;
    cout << "Choose game mode:\n1. Two-player\n2. Play against random AI\n3. Play against Minimax AI\nEnter your choice: ";
    cin >> gameMode;

    while (true) {
        displayBoard();
        if (currentPlayer == 'X' || gameMode == 1) {
            playerMove(currentPlayer);
        } else if (gameMode == 2) {
            aiMove();
        } else if (gameMode == 3) {
            minimaxAiMove();
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