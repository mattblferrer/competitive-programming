#include <array>
#include <iostream>
#include <vector>

void ABC109D() {
    int h, w;
    std::cin >> h >> w;
    int** a = new int*[h];
    for (int i = 0; i < h; i++) {
        a[i] = new int[w];
        for (int j = 0; j < w; j++) {
            std::cin >> a[i][j];
        }
    }
    int count = 0;
    std::vector<std::array<int, 4>> moves;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] % 2 == 0) {
                continue;
            }
            if (!((i < h - 1) || (j < w - 1))) {
                continue;
            }
            std::array<int, 4> move;
            if (i < h - 1) {
                a[i][j]--;
                a[i + 1][j]++;
                move = {i + 1, j + 1, i + 2, j + 1};
            }
            else if (j < w - 1) {
                a[i][j]--;
                a[i][j + 1]++;
                move = {i + 1, j + 1, i + 1, j + 2};
            } 
            moves.push_back(move);
            count++;
        }
    }
    std::cout << count << "\n";
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << moves[i][j] << " ";
        }
        std::cout << moves[i][3] << "\n";
    }
}

int main() {
    ABC109D();
    return 0;
}