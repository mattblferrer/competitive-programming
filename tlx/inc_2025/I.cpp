#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
// #define DEBUG
using lng = long long;
using lll = __int128;
template<typename T> 
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int const INF32 = 0x3f3f3f3f;
lng const INF64 = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<string>> grid(n + 2, vector<string>(m + 2, "#"));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) { 
            char c;
            cin >> c;
            
            grid[i][j] = "";
            grid[i][j] += c;
        }

    auto getStr = [&](int i, int j) -> string {
        assert(i <= n && j <= m);
        return grid[i][j] + grid[i][j + 1] + grid[i + 1][j] + grid[i + 1][j + 1];
    };

    set<string> S = {"...#", "..#.", ".#..", "#..."};
    set<pair<int, int>> not_good;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            string s = getStr(i, j);
            if (S.find(s) != S.end())
                not_good.insert({i, j});
        }

    int q;
    cin >> q;
    while (q--) {
        int i, j;
        cin >> i >> j;

        if (grid[i][j] == ".")
            grid[i][j] = "#";
        else if (grid[i][j] == "#")
            grid[i][j] = ".";

        // for (int i = 1; i <= n; i++) {
        //     for (int j = 1; j <= m; j++)
        //         cout << grid[i][j];
        //     cout << endl;
        // }

        i--;
        j--;

        for (int di : {0, 1})
            for (int dj : {0, 1}) {
                string s = getStr(i + di, j + dj);
                if (S.find(s) == S.end()) {
                    if (not_good.find({i + di, j + dj}) != not_good.end())
                        not_good.erase({i + di, j + dj});
                } else {
                    not_good.insert({i + di, j + dj});
                }
            }
            
        cout << (not_good.size() == 0 ? "RECTANGLES" : "NO") << endl;
    }
    
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}