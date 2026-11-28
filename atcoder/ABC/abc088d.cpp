#include <bits/stdc++.h>

int ABC088D() {
    int h, w;
    std::cin >> h >> w;
    std::vector<std::string> s(h);
    for (int i = 0; i < h; i++) {
        std::cin >> s[i];
    }
    int bl = 0;  // black squares
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') bl++;
        }
    }
    std::vector<std::vector<int>> dist(h, std::vector<int>(w, 10000));
    dist[0][0] = 1;
    std::queue<std::pair<int, int>> q;
    q.push({0, 0});

    while (!q.empty()) {
        std::pair<int, int> u = q.front();
        q.pop();
        int x = u.first;
        int y = u.second;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == j || i == -j) continue;
                if (x + i < 0 || x + i >= h || y + j < 0 || y + j >= w) continue;
                if (dist[x + i][y + j] != 10000) continue;
                if (s[x + i][y + j] == '#') continue;
                dist[x + i][y + j] = dist[x][y] + 1;
                q.push({x + i, y + j});
            }
        }
    }
    if (dist[h - 1][w - 1] == 10000) return -1;
    else return h * w - bl - dist[h - 1][w - 1];
}

int main() {
    std::cout << ABC088D();
    return 0;
}