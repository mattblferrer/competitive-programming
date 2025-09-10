#include <bits/stdc++.h>

void problemA() {
    int INF = 2000000001;
    int n, m, a_i, b_i, d_i;
    std::cin >> n;
    std::vector<int> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }

    // expand weighted graph to graph with only edges of length 1
    std::cin >> m;
    std::vector<std::vector<int>> adj_list(200 + m * 200);
    std::vector<int> dist(200 + m * 200, INF);
    for (int i = 1; i <= m; i++) {
        std::cin >> a_i >> b_i >> d_i;
        if (d_i > 1) {
            adj_list[a_i - 1].push_back(i * 200 + 1);
            for (int j = 1; j < d_i - 1; j++) {
                adj_list[i * 200 + j].push_back(i * 200 + j + 1);
            }
            adj_list[i * 200 + d_i - 1].push_back(b_i - 1);
            adj_list[b_i - 1].push_back(i * 200 + d_i - 1);
            for (int j = d_i - 1; j > 0; j--) {
                adj_list[i * 200 + j + 1].push_back(i * 200 + j);
            }
            adj_list[i * 200 + 1].push_back(a_i - 1);
        }
        else {
            adj_list[a_i - 1].push_back(b_i - 1);
            adj_list[b_i - 1].push_back(a_i - 1);
        }
    }

    // bfs on graph 
    std::vector<int> max_items(200 + m * 200);
    std::queue<std::pair<int, int>> q;
    q.push({0, t[0]});
    dist[0] = 0;
    while (!q.empty()) {
        std::pair<int, int> curr = q.front();
        int u = curr.first;
        int items = curr.second;
        q.pop();

        max_items[u] = std::max(max_items[u], items);
        items = max_items[u];
        for (int v: adj_list[u]) {
            if (dist[v] < dist[u] + 1) continue;
            dist[v] = dist[u] + 1;
            
            if (v < n) q.push({v, items + t[v]});
            else q.push({v, items});
        }
    }
    
    // output if not reached, else output min length and max items
    if (dist[n - 1] == INF)  {
        std::cout << "impossible";
        return;
    }
    std::cout << dist[n - 1] << " " << max_items[n - 1];
}

int main() {
    problemA();
    return 0;
}