#include <bits/stdc++.h>

std::string problem510B() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }

    std::vector<std::vector<int>> dist(n, std::vector<int> (m, n * m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[i][j] != n * m + 1) continue;
            std::queue<std::pair<int, int>> q;
            q.push({i, j});
            dist[i][j] = 0;

            while (!q.empty()) {
                std::pair<int, int> u = q.front();
                q.pop();
                int y = u.first;
                int x = u.second;

                if (y != 0 && d[y - 1][x] == d[y][x]) {
                    if (dist[y - 1][x] == n * m + 1) {
                        q.push({y - 1, x});
                        dist[y - 1][x] = dist[y][x] + 1;
                    }
                    else if (dist[y - 1][x] != dist[y][x] - 1) return "Yes";
                }
                if (y != n - 1 && d[y + 1][x] == d[y][x]) {
                    if (dist[y + 1][x] == n * m + 1){
                        q.push({y + 1, x});
                        dist[y + 1][x] = dist[y][x] + 1;
                    }
                    else if (dist[y + 1][x] != dist[y][x] - 1) return "Yes";
                }
                if (x != 0 && d[y][x - 1] == d[y][x]) {
                    if (dist[y][x - 1] == n * m + 1) {
                        q.push({y, x - 1});
                        dist[y][x - 1] = dist[y][x] + 1;
                    }
                    else if (dist[y][x - 1] != dist[y][x] - 1) return "Yes";
                }
                if (x != m - 1 && d[y][x + 1] == d[y][x]) {
                    if (dist[y][x + 1] == n * m + 1) {
                        q.push({y, x + 1});
                        dist[y][x + 1] = dist[y][x] + 1;
                    }
                    else if (dist[y][x + 1] != dist[y][x] - 1) return "Yes";
                }
            }
        }
    }

    return "No";
}

int main() {
    std::cout << problem510B();
    return 0;
}