#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

const int BOARD_SIZE = 4;

class Game2048 {
private:
    vector<vector<int>> board;
    int score;

    void addNewTile() {
        vector<pair<int, int>> emptyTiles;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == 0) {
                    emptyTiles.push_back({i, j});
                }
            }
        }
        if (!emptyTiles.empty()) {
            int index = rand() % emptyTiles.size();
            int value = (rand() % 2 + 1) * 2; // 2 or 4
            board[emptyTiles[index].first][emptyTiles[index].second] = value;
        }
    }

    bool moveTiles(int direction) {
        bool moved = false;
        if (direction == 0 || direction == 2) { // Up or Down
            for (int j = 0; j < BOARD_SIZE; ++j) {
                vector<int> column;
                for (int i = 0; i < BOARD_SIZE; ++i) {
                    if (board[i][j] != 0) {
                        column.push_back(board[i][j]);
                    }
                }
                if (direction == 2) reverse(column.begin(), column.end());
                for (int i = 1; i < column.size(); ++i) {
                    if (column[i] == column[i-1]) {
                        column[i-1] *= 2;
                        score += column[i-1];
                        column[i] = 0;
                        moved = true;
                    }
                }
                column.erase(remove(column.begin(), column.end(), 0), column.end());
                while (column.size() < BOARD_SIZE) column.push_back(0);
                if (direction == 2) reverse(column.begin(), column.end());
                for (int i = 0; i < BOARD_SIZE; ++i) {
                    if (board[i][j] != column[i]) {
                        board[i][j] = column[i];
                        moved = true;
                    }
                }
            }
        } else { // Left or Right
            for (int i = 0; i < BOARD_SIZE; ++i) {
                vector<int> row;
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (board[i][j] != 0) {
                        row.push_back(board[i][j]);
                    }
                }
                if (direction == 1) reverse(row.begin(), row.end());
                for (int j = 1; j < row.size(); ++j) {
                    if (row[j] == row[j-1]) {
                        row[j-1] *= 2;
                        score += row[j-1];
                        row[j] = 0;
                        moved = true;
                    }
                }
                row.erase(remove(row.begin(), row.end(), 0), row.end());
                while (row.size() < BOARD_SIZE) row.push_back(0);
                if (direction == 1) reverse(row.begin(), row.end());
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    if (board[i][j] != row[j]) {
                        board[i][j] = row[j];
                        moved = true;
                    }
                }
            }
        }
        return moved;
    }

public:
    Game2048() : board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0)), score(0) {
        srand(time(0));
        addNewTile();
        addNewTile();
    }

    void printBoard() {
        cout << "Score: " << score << endl;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                cout << setw(5) << board[i][j];
            }
            cout << endl;
        }
    }

    bool makeMove(char direction) {
        int dir;
        switch(direction) {
            case 'w': dir = 0; break; // Up
            case 'd': dir = 1; break; // Right
            case 's': dir = 2; break; // Down
            case 'a': dir = 3; break; // Left
            default: return false;
        }
        bool moved = moveTiles(dir);
        if (moved) {
            addNewTile();
        }
        return true;
    }

    bool isGameOver() {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (board[i][j] == 0) return false;
                if (i > 0 && board[i][j] == board[i-1][j]) return false;
                if (j > 0 && board[i][j] == board[i][j-1]) return false;
            }
        }
        return true;
    }
};

int main() {
    Game2048 game;
    char move;
    while (!game.isGameOver()) {
        game.printBoard();
        cout << "Enter move (w/a/s/d): ";
        cin >> move;
        if (game.makeMove(move)) {
            system("cls"); // Use "cls" for Windows
        }
    }
    cout << "Game Over!" << endl;
    game.printBoard();
    return 0;
}
