#include <bits/stdc++.h>

int ABC151D() {
    int h, w;
    std::cin >> h >> w;
    std::vector<std::vector<char>> s(h + 2, std::vector<char>(w + 2, '#'));
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            std::cin >> s[i][j];
        }
    }   

    int max_dist = 0;
    for (int i = 1; i <= h; i++) {  // try every starting square
        for (int j = 1; j <= w; j++) {
            if (s[i][j] == '#') continue;
            std::vector<std::vector<int>> dist(h + 2, std::vector<int>(w + 2, h * w + 1));
            dist[i][j] = 0;
            std::queue<std::pair<int, int>> q;
            q.push({i, j});
            
            while (!q.empty()) {
                std::pair<int, int> u = q.front();
                q.pop();
                int x = u.first;
                int y = u.second;

                if (dist[x - 1][y] == h * w + 1 && s[x - 1][y] == '.') {
                    dist[x - 1][y] = dist[x][y] + 1;
                    q.push({x - 1, y});
                }
                if (dist[x + 1][y] == h * w + 1 && s[x + 1][y] == '.') {
                    dist[x + 1][y] = dist[x][y] + 1;
                    q.push({x + 1, y});
                }
                if (dist[x][y + 1] == h * w + 1 && s[x][y + 1] == '.') {
                    dist[x][y + 1] = dist[x][y] + 1;
                    q.push({x, y + 1});
                }
                if (dist[x][y - 1] == h * w + 1 && s[x][y - 1] == '.') {
                    dist[x][y - 1] = dist[x][y] + 1;
                    q.push({x, y - 1});
                }
            }
            for (int i = 1; i <= h; i++) {
                for (int j = 1; j <= w; j++) {
                    if (s[i][j] == '.') max_dist = std::max(max_dist, dist[i][j]);
                }
            }
        }
    }
    
    return max_dist;
}

int main() {
    std::cout << ABC151D();
    return 0;
}