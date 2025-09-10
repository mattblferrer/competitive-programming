#include <bits/stdc++.h>

std::vector<std::string> board(8);
std::set<std::vector<std::string>> seen;

int search(int q) {
    if (seen.count(board)) return 0;
    seen.insert(board);
    if (q == 8) {
        return 1;
    }
    int ans = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == '*' || board[i][j] == 'Q') continue;
            bool valid = true;
            for (int k = 0; k < 8; k++) {
                if (i == k) continue;
                if (board[k][j] == 'Q') valid = false;
            }
            for (int k = 0; k < 8; k++) {
                if (j == k) continue;
                if (board[i][k] == 'Q') valid = false;
            }
            for (int k = 1; k < 8; k++) {
                if (0 <= i - k && i - k < 8 && 0 <= j - k && j - k < 8) {
                    if (board[i - k][j - k] == 'Q') valid = false;
                }
                if (0 <= i + k && i + k < 8 && 0 <= j + k && j + k < 8) {
                    if (board[i + k][j + k] == 'Q') valid = false;
                } 
                if (0 <= i - k && i - k < 8 && 0 <= j + k && j + k < 8) {
                    if (board[i - k][j + k] == 'Q') valid = false;
                } 
                if (0 <= i + k && i + k < 8 && 0 <= j - k && j - k < 8) {
                    if (board[i + k][j - k] == 'Q') valid = false;
                } 
            }
            if (valid) {
                board[i][j] = 'Q';
                ans += search(q + 1);
                board[i][j] = '.';
            }
        }
    }
    return ans;
}

int CSES1624() {
    for (int i = 0; i < 8; i++) {
        std::cin >> board[i];
    }
    return search(0);
}

int main() {
    std::cout << CSES1624();
    return 0;
}