#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
class Board {
private:
    vector<char> board;
public:
    Board() : board(9, ' ') {}

    void display() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << board[i * 3 + j];
                if (j < 2) cout << '|';
            }
            cout << endl;
            if (i < 2) cout << "-----" << endl;
        }
    }

    bool checkWin(char marker) {
        return (board[0] == marker && board[1] == marker && board[2] == marker) ||  // rows
            (board[3] == marker && board[4] == marker && board[5] == marker) ||
            (board[6] == marker && board[7] == marker && board[8] == marker) ||
            (board[0] == marker && board[3] == marker && board[6] == marker) ||  // columns
            (board[1] == marker && board[4] == marker && board[7] == marker) ||
            (board[2] == marker && board[5] == marker && board[8] == marker) ||
            (board[0] == marker && board[4] == marker && board[8] == marker) ||  // diagonals
            (board[2] == marker && board[4] == marker && board[6] == marker);
    }

    bool isFull() {
        for (char cell : board) {
            if (cell == ' ') return false;
        }
        return true;
    }

    void placeMarker(int position, char marker) {
        board[position] = marker;
    }

    char getMarker(int position) {
        return board[position];
    }
};

class Player {
public:
    char marker;

    Player(char _marker) : marker(_marker) {}

    virtual int getMove(Board& board) = 0;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(char _marker) : Player(_marker) {}

    int getMove(Board& board) override {
        int move;
        while (true) {
            cout << "Enter your move (1-9): ";
            cin >> move;
            move--;
            if (move >= 0 && move < 9 && board.getMarker(move) == ' ') {
                return move;
            }
            else {
                cout << "Invalid move. Please choose an empty position." << endl;
            }
        }
    }
};

class ComputerPlayer : public Player {
public:
    ComputerPlayer(char _marker) : Player(_marker) {}

    int getMove(Board& board) override {
        vector<int> availableMoves;
        for (int i = 0; i < 9; ++i) {
            if (board.getMarker(i) == ' ') {
                availableMoves.push_back(i);
            }
        }
        srand(time(0));
        return availableMoves[rand() % availableMoves.size()];
    }
};

class Game {
private:
    Board board;
    Player* player1;
    Player* player2;

public:
    Game() : player1(nullptr), player2(nullptr) {}

    void selectPlayers() {
        string player1Type, player2Type;
        while (true) {
            cout << "Select player 1 type (human/computer): ";
            cin >> player1Type;
            if (player1Type == "human" || player1Type == "computer") break;
            else cout << "Invalid player type. Please choose \"human\" or \"computer\"." << endl;
        }
        while (true) {
            cout << "Select player 2 type (human/computer): ";
            cin >> player2Type;
            if (player2Type == "human" || player2Type == "computer") break;
            else cout << "Invalid player type. Please choose \"human\" or \"computer\"." << endl;
        }

        if (player1Type == "human") player1 = new HumanPlayer('X');
        else player1 = new ComputerPlayer('X');

        if (player2Type == "human") player2 = new HumanPlayer('O');
        else player2 = new ComputerPlayer('O');
    }

    void play() {
        selectPlayers();
        Player* currentPlayer = player1;
        while (!board.isFull()) {
            board.display();
            cout << endl;

            int move = currentPlayer->getMove(board);
            board.placeMarker(move, currentPlayer->marker);

            if (board.checkWin(currentPlayer->marker)) {
                board.display();
                cout << "Player " << currentPlayer->marker << " wins!" << endl;
                break;
            }
            else if (board.isFull()) {
                board.display();
                cout << "It's a tie!" << endl;
                break;
            }

            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }
        delete player1;
        delete player2;
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
