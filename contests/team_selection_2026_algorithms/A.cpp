#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> dr = {0, -1, 0, 1};
vector<int> dc = {1, 0, -1, 0};

void solve() {
    int r, c, n;
    cin >> r >> c >> n;
    vector<vector<int>> towers(r, vector<int>(c));
    vector<vector<int>> closest(r, vector<int>(c)), closest2(r, vector<int>(c));
    queue<vector<int>> q;
    for (int i = 0; i < n; i++) {
        int ri, ci;
        cin >> ri >> ci;
        ri--; ci--;
        towers[ri][ci] = i + 1;
        closest[ri][ci] = i + 1;
        q.push({ri, ci, i + 1});
    }

    while (!q.empty()) {
        int pr = q.front()[0], pc = q.front()[1], t = q.front()[2];
        q.pop();
        for (int d = 0; d < 4; d++) {
            int nr = pr + dr[d], nc = pc + dc[d];
            if (nr < 0 || nr >= r) continue;
            if (nc < 0 || nc >= c) continue;
            if (closest[nr][nc] == 0) {
                closest[nr][nc] = t;
                q.push({nr, nc, t});
            }
            else if (closest2[nr][nc] == 0 && closest[nr][nc] != t) {
                closest2[nr][nc] = t;
                q.push({nr, nc, t});
            }
        }
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) cout << closest[i][j] << " ";
        cout << "\n";
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) cout << closest2[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    solve();
    return 0;
}