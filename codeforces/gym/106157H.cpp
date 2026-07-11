#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int START_IDX = 1;
void solve() {
    // your solution here
    int n, k;
    cin >> n >> k;
    k--;

    vector<int> parent(n, -1);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        int l, r;
        cin >> l >> r;
        l--; r--;
        adj[l].push_back(r);
        adj[r].push_back(l);
    }

    vector<int> dfs_time(n, 0);
    vector<int> bfs_time(n, 0);

    int dfs_idx = START_IDX;
    auto dfs = [&](auto &&self, int v, int p) -> void
        {
            dfs_time[v] = dfs_idx;
            dfs_idx++;
            for (int c : adj[v])
            {
                if (c == p) continue;
                parent[c] = v;
                self(self, c, v);
            }
        };

    dfs(dfs, 0, -1);

    int bfs_idx = START_IDX;
    auto bfs = [&](int v)
        {
            deque<int> to_visit;
            to_visit.push_back(v);
            vector<int> visited(n);
            visited[v] = true;
            while (!to_visit.empty())
            {
                int cur = to_visit.front();
                to_visit.pop_front();

                bfs_time[cur] = bfs_idx++;
                for (int c : adj[cur])
                {
                    if (!visited[c])
                    {
                        visited[c] = true;
                        to_visit.push_back(c);
                    }
                }
            }
        };
    bfs(0);

    vector<int> k_ancestors;
    k_ancestors.push_back(k);
    while (parent[k_ancestors.back()] != -1)
    {
        k_ancestors.push_back(parent[k_ancestors.back()]);
    }

    vector<bool> is_k_ancestor(n, false);
    for (int i : k_ancestors) is_k_ancestor[i] = true;

    vector<int> bfs_to_k(n, 0);

    int dfs_ans = dfs_time[k];
    int bfs_ans = bfs_time[k];
    // review
    auto get_bfs_to_k = [&](auto &&self, int v, int p) -> int
        {
            int total = 0;
            for (int c : adj[v])
            {
                if (c == p) continue;
                total += self(self, c, v);
            }
            return bfs_to_k[v] = (total)+((bfs_time[v] < bfs_time[k]) ? 1 : 0);
        };

    get_bfs_to_k(get_bfs_to_k, 0, -1);

    for (int i : k_ancestors)
    {
        bfs_ans = min(bfs_ans, bfs_time[i] + (dfs_time[k] - dfs_time[i]));
        dfs_ans = min(dfs_ans, dfs_time[i] + bfs_to_k[i]);
    }
    cout << bfs_ans << "\n" << dfs_ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}