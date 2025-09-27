#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

ll find_depths(vector<ll>& depths, vector<vector<ll>>& adj, int start)
{
    if (depths[start] != -1) return depths[start];
    if (adj[start].size() == 0) depths[start] = 0;
    for (ll child : adj[start])
    {
        depths[start] = max(depths[start], 1 + find_depths(depths, adj, child));
    }
    return depths[start];
}

void solve() {
    int n;
    cin >> n;
    vector<vector<ll>> adj_list(n);
    vector<ll> parent_count(n, 0);
    int child_count;
    for (int i = 0; i < n; i++)
    {
        cin >> child_count;
        for (int j = 0; j < child_count; j++)
        {
            ll child;
            cin >> child;
            child--;
            adj_list[i].push_back(child);
            parent_count[child]++; 
        }
    }

    vector<int> roots;
    for (int i = 0; i < n; i++)
    {
        if (parent_count[i] == 0) roots.push_back(i);
    }

    vector<ll> depths(n, -1);
    for (int i : roots)
    {
        find_depths(depths, adj_list, i);
    }

    ll max_depth = *max_element(depths.begin(), depths.end());
    if (max_depth == n - 1) cout << 1;
    else cout << 0;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}