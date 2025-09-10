#include <bits/stdc++.h>

void ABC075B() {
    int h, w;
    std::cin >> h >> w;
    std::vector<std::string> board(h);
    for (int i = 0; i < h; i++) {
        std::cin >> board[i];
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (board[i][j] == '#') continue;
            int bombs = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0) continue;
                    if (i + k < 0 || i + k >= h || j + l < 0 || j + l >= w) continue;
                    if (board[i + k][j + l] == '#') bombs++;
                }
            }
            board[i][j] = bombs + '0';
        }
    }
    for (int i = 0; i < h; i++) {
        std::cout << board[i] << '\n';
    }
}

int main() {
    ABC075B();
    return 0;
}