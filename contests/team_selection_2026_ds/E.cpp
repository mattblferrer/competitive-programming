#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    map<int, set<int>> spies_x;
    map<int, set<int>> spies_y;
    vector<bool> elim(n + 1);
    vector<pair<int, int>> loc(n + 1);
    map<pair<int, int>, int> team;

    for (int i = 1; i <= n; i++) {
        int xi, yi;
        cin >> xi >> yi;
        spies_x[xi].insert(yi);
        spies_y[yi].insert(xi);
        loc[i] = {xi, yi};
        team[{xi, yi}] = i;
    }
    for (int i = 1; i <= m; i++) {
        int ti;
        char dir;
        cin >> ti >> dir;
        if (elim[ti]) {
            cout << "ignore\n";
            continue;
        }

        int xi = loc[ti].first, yi = loc[ti].second;
        vector<int> curr;
        if (dir == 'N') {
            int y = *(spies_x[xi].rbegin());
            while (y > yi) {
                spies_x[xi].erase(y);
                if (!elim[team[{xi, y}]]) curr.push_back(team[{xi, y}]);
                elim[team[{xi, y}]] = true;
                y = *(spies_x[xi].rbegin());
            }
        }
        else if (dir == 'S') {
            int y = *(spies_x[xi].begin());
            while (y < yi) {
                spies_x[xi].erase(y);
                if (!elim[team[{xi, y}]]) curr.push_back(team[{xi, y}]);
                elim[team[{xi, y}]] = true;
                y = *(spies_x[xi].begin());
            }
        }
        else if (dir == 'E') {
            int x = *(spies_y[yi].rbegin());
            while (x > xi) {
                spies_y[yi].erase(x);
                if (!elim[team[{x, yi}]]) curr.push_back(team[{x, yi}]);
                elim[team[{x, yi}]] = true;
                x = *(spies_y[yi].rbegin());
            }
        }
        else if (dir == 'W') {
            int x = *(spies_y[yi].begin());
            while (x < xi) {
                spies_y[yi].erase(x);
                if (!elim[team[{x, yi}]]) curr.push_back(team[{x, yi}]);
                elim[team[{x, yi}]] = true;
                x = *(spies_y[yi].begin());
            }
        }
        cout << curr.size() << " ";
        for (int i = curr.size() - 1; i >= 0; i--) cout << curr[i] << " ";
        cout << "\n";
    }

    return 0;
}