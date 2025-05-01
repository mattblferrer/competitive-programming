#include <bits/stdc++.h>

void problem377A() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::string> maze(n);
    for (int i = 0; i < n; i++) {
        std::cin >> maze[i];
    }

    std::vector<std::vector<int>> dist(n, std::vector<int>(m, 99999));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == '#' || dist[i][j] != 99999) continue;
            dist[i][j] = 0;
            std::queue<std::pair<int, int>> q;
            q.push({i, j});

            while (!q.empty()) {
                std::pair<int, int> u = q.front();
                q.pop();
                int x = u.first;
                int y = u.second;
                if (x != 0 && maze[x - 1][y] == '.' && dist[x - 1][y] == 99999) {
                    q.push({x - 1, y});
                    dist[x - 1][y] = dist[x][y] + 1;
                }
                if (x != n - 1 && maze[x + 1][y] == '.' && dist[x + 1][y] == 99999) {
                    q.push({x + 1, y});
                    dist[x + 1][y] = dist[x][y] + 1;
                }
                if (y != 0 && maze[x][y - 1] == '.' && dist[x][y - 1] == 99999) {
                    q.push({x, y - 1});
                    dist[x][y - 1] = dist[x][y] + 1;
                }
                if (y != m - 1 && maze[x][y + 1] == '.' && dist[x][y + 1] == 99999) {
                    q.push({x, y + 1});
                    dist[x][y + 1] = dist[x][y] + 1;
                }
            }
        }
    }
    std::priority_queue<std::vector<int>> dist_sorted;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[i][j] == 99999) continue;
            std::vector<int> u = {dist[i][j], i, j};
            dist_sorted.push(u);
        }
    }
    for (int i = 0; i < k; i++) {
        std::vector<int> u = dist_sorted.top();
        maze[u[1]][u[2]] = 'X';  
        dist_sorted.pop();
    }
    for  (int i = 0; i < n; i++) {
        std::cout << maze[i] << '\n';
    }
}

int main() {
    problem377A();
    return 0;
}