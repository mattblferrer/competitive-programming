#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const int INF = 2e9;

void solve() {
    int h, w, k;
    cin >> h >> w >> k;
    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
        cin >> grid[i];
    }

    // count bombs in rows, cols
    vector<int> brows(h), bcols(w);
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '#') {
                brows[i]++;
                bcols[j]++;
            }
        }
    }

    vector<pair<int, int>> safe_empty;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == '#') continue;
            if ((brows[i] == 0) && (bcols[j] == 0)) {
                safe_empty.push_back({i, j});
            }
        }
    }
    vector<vector<int>> dist(h, vector<int>(w, INF));
    queue<pair<int, int>> q;
    for (auto &[i, j] : safe_empty) {
        dist[i][j] = 0;
    }

    vector<int> di = {-1, 0, 1, 0};
    vector<int> dj = {0, -1, 0, 1};
    vector<vector<vector<bool>>> edges(h, vector<vector<bool>>(w, vector<bool>(4)));
    for (auto &[start_i, start_j] : safe_empty) {
        q.push({start_i, start_j});
        while (!q.empty()) {
            auto pair = q.front();
            q.pop();
            int i = pair.first, j = pair.second;

            for (int ct = 0; ct < 4; ct++) {
                int ni = i + di[ct], nj = j + dj[ct];

                if ((ni < 0) || (ni >= h)) continue;
                if ((nj < 0) || (nj >= w)) continue;
                if (grid[ni][nj] == '#') continue;
                if (edges[i][j][ct]) continue;

                dist[ni][nj] = min(dist[ni][nj], dist[i][j] + 1);
                edges[i][j][ct] = true;
                q.push({ni, nj});
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (dist[i][j] <= k) ans++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}