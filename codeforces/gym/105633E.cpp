#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
bool valid (ll n, ll m, ll x, ll y)
{
    return x >= 0 && x < n && y >= 0 && y < m;
}

ll dfs(set<ll>& visited, vector<vector<char>>& graph, vector<vector<ll>>& adj, ll start)
{
    ll n = graph.size();
    ll m = graph[0].size();
    vector<ll> results;
    visited.insert(start);
    for (ll child : adj[start])
    {
        if (visited.count(child) == 0)
        {
            ll result = dfs(visited, graph, adj, child);
            results.push_back(result);
        }
    }

    char op = graph[start / m][start % m];
    switch (op)
    {
        case '+':
            return results[0] + results[1];
            break;
        case '-':
            return abs(results[0] - results[1]);
            break;
        case '*':
            return results[0] * results[1];
            break;
        case '/':
            return (results[0] > results[1]) ? (results[0] / results[1]) : (results[1] / results[0]);
            break;
        case '#':
            return results[0];
            break;
        case 'P':
            cout << results[0];
            return 0;
        default:
            return (ll) ((ll) op - (ll) '0');
            break;
    }
    return 0;
    
} 

vector<vector<ll>> translations = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
void solve() {
    ll n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m, 0));
    for (ll i = 0; i < n; i++) for (ll j = 0; j < m; j++) cin >> grid[i][j];

    ll total_size = n*m;
    vector<vector<ll>> adj(total_size);
    ll prller_index = -1;
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < m; j++)
        {
            ll cur_id = i * m + j;
            if (grid[i][j] == '.') continue;
            if (grid[i][j] == 'P') prller_index = cur_id;
            for (vector<ll> translation : translations)
            {
                ll dx = translation[0];
                ll dy = translation[1];
                // cout << i << " " << j << " " << i + dy << " " << j + dx << "\n";
                if (valid(n, m, i + dy, j + dx))
                {
                    if (grid[i + dy][j + dx] == '.') continue;
                    ll new_id = (i + dy) * m + j + dx;
                    adj[cur_id].push_back(new_id);
                }
            }
        }
    }

    // for (ll i = 0; i < total_size; i++)
    // {
    //     cout << i << " children: ";
    //     for (ll child : adj[i])
    //     {
    //         cout << child << " ";
    //     }
    //     cout << "\n";
    // }
    set<ll> visited;
    dfs(visited, grid, adj, prller_index);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}