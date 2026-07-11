#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int ALPHABET = 26;
bool is_cyclic_util(vector<vector<int>> &adj, int u, vector<bool> &visited, vector<bool> &rec_stack) {

    if (rec_stack[u]) return true;
    if (visited[u]) return false;

    visited[u] = true;
    rec_stack[u] = true;

    for (int v : adj[u]) {
        if (is_cyclic_util(adj, v, visited, rec_stack))
            return true;
    }

    rec_stack[u] = false;
    return false;
}

bool is_cyclic(vector<vector<int>> &adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<bool> rec_stack(V, false);

    // Run DFS from every unvisited node
    for (int i = 0; i < V; i++) {
        if (!visited[i] && is_cyclic_util(adj, i, visited, rec_stack))
            return true;
    }
    return false;
}

void solve() {
    // your solution here
    int n;
    cin >> n;

    vector<vector<int>> adj(ALPHABET);
    for (int i = 0; i < n; i++)
    {
        char u, op, v;
        cin >> u >> op >> v;
        int new_u = u - 'a';
        int new_v = v - 'a';
        if (op == '<') swap(new_u, new_v);
        adj[new_u].push_back(new_v);
    }

    vector<char> letters;
    string s;
    cin >> s;
    for (char c : s) letters.push_back(c);

    if (is_cyclic(adj))
    {
        cout << "IMPOSSIBLE";
        return;
    }

    vector<int> indegree(ALPHABET, 0);
    deque<int> to_visit;
    for (int i = 0; i < ALPHABET; i++)
    {
        for (int child : adj[i])
        {
            indegree[child]++;
        }
    }

    for (int i = 0; i < ALPHABET; i++)
    {
        if (indegree[i] == 0)
        {
            to_visit.push_back(i);
        }
    }

    vector<int> vals(ALPHABET, 2391);
    vector<bool> visited(ALPHABET, false);
    while (!to_visit.empty())
    {
        int cur_node = to_visit.front();
        to_visit.pop_front();

        for (int child : adj[cur_node])
        {
            vals[child] = min(vals[cur_node] - 1, vals[child]);
            indegree[child]--;
            if (indegree[child] == 0)
            {
                to_visit.push_back(child);
            }
        }
    }

    auto char_comp = [&](const char &a, const char &b) -> bool
        {
            return vals[a - 'a'] < vals[b - 'a'];
        };

    sort(letters.begin(), letters.end(), char_comp);
    for (char c : letters) cout << c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}