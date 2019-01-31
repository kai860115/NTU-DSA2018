#include <cstring>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <iostream>
#include <string>
 
using namespace std;
 
#define O 0x2
#define X 0x1
#define XALL 0x1555555555555
#define OALL 0x2aaaaaaaaaaaa
 
//X win 1, O win -1
int getScore(size_t board) {
    board = (~board & OALL) >> 1 | board;
    size_t x_score[12] = {0x1550000000000, 0x5540000000, 0x15500000, 0x55400, 0x155, 0x1004010040100, 0x401004010040, 0x100401004010, 0x40100401004, 0x10040100401, 0x1001001001001, 0x10101010100};
    int n_x[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int score = 0;
    for (size_t i = 0; i != 12; i++) {
        n_x[i] = __builtin_popcountll((board & x_score[i]));
        if (n_x[i] >= 4)
            score++;
        else if (n_x[i] <= 1)
            score--;
    }
    if (score >= 1)
        return 1;
    else if (score <= -1)
        return -1;
    else
        return 0;
}
 
void generateNext(const size_t &board, vector<size_t> &vec, const size_t &n_round) {
    size_t step = 0;
    if (n_round == 11)
        return;
    if ((n_round & 1))
        step = X;
    else
        step = O;
    vec.reserve(1000);
    vector<size_t>::iterator it = vec.begin();
    size_t firstStep = step;
    size_t secondStep = step;
 
    for (size_t i = 0; i < 25; i++) {
        if (((board >> (2 * i)) & 3) == 0) {
            firstStep = (step << (2 * i));
            for (size_t j = i + 1; j < 25; j++) {
                if (((board >> (2 * j)) & 3) == 0) {
                    secondStep = (step << (2 * j));
                    vec.insert(it++, (board | firstStep | secondStep));
                }
            }
        }
    }
}
 
int alpha_beta(const size_t &board, int alpha, int beta, const size_t &n_round, unordered_map<size_t, int> &board_map) {
    size_t board_key = board | (size_t(alpha) << 55) | (size_t(beta) << 53);
    if (board_map.find(board_key) != board_map.end()) {
        return board_map[board_key];
    } else {
        if (n_round == 11) {
            int score = getScore(board);
            board_map[board_key] = score;
            return score;
        }
        vector<size_t> next_board;
        if ((n_round & 1)) {
            int best_score = -1;
            generateNext(board, next_board, n_round);
            for (vector<size_t>::iterator it = next_board.begin(); it != next_board.end(); it++) {
                int score = alpha_beta(*it, alpha, beta, n_round + 1, board_map);
                if (score > alpha)
                    alpha = score;
                if (alpha >= beta)
                    break;
            }
            board_map[board_key] = alpha;
            return alpha;
        } else {
            generateNext(board, next_board, n_round);
            for (vector<size_t>::iterator it = next_board.begin(); it != next_board.end(); it++) {
                int score = alpha_beta(*it, alpha, beta, n_round + 1, board_map);
                if (score < beta)
                    beta = score;
                if (alpha >= beta)
                    break;
            }
            board_map[board_key] = beta;
            return beta;
        }
    }
}
 
int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(0);
    size_t n_board;
    cin >> n_board;
    unordered_map<size_t, int> board_map;
    for (size_t i = 0; i < n_board; i++) {
        size_t board = 0;
        size_t n_round = 0;
        for (size_t row = 0; row != 5; row++) {
            char c[6];
            cin >> c;
            for (size_t col = 0; col != 5; col++) {
                board = board << 2;
                if (c[col] == 'O') {
                    board = board | O;
                    n_round++;
                } else if (c[col] == 'X') {
                    board = board | X;
                    n_round++;
                }
            }
        }
        n_round /= 2;
        int score = alpha_beta(board, -1, 1, n_round, board_map);
        switch (score) {
            case -1:
                cout << "O win\n";
                break;
            case 1:
                cout << "X win\n";
                break;
            default:
                cout << "Draw\n";
                break;
        }
    }
 
    return 0;
}
