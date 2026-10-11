#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> inbound(n);
    vector<set<int>> outbound(n);
    for (int i = 0; i < m; i++)
    {
        int l, r; cin >> l >> r; l--; r--;
        inbound[r].push_back(l);
        outbound[l].insert(r);
    }

    int max_score = 0;
    int max_idx = 0;
    for (int i = 0; i < n; i++)
    {
        int cur_score = inbound[i].size();
        for (int j : inbound[i])
        {
            if (outbound[i].count(j) != 0)
            {
                cur_score--;
            }
        }

        if (cur_score > max_score)
        {
            max_idx = i;
            max_score = cur_score;
        }
    }

    cout << max_idx + 1 << " " << max_score << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}