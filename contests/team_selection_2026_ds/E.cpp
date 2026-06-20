#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

int main() {
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
            while (*prev(spies_x[xi].end()) > yi) {
                int y = *prev(spies_x[xi].end());
                spies_x[xi].erase(y);
                if (!elim[team[{xi, y}]]) curr.push_back(team[{xi, y}]);
                elim[team[{xi, y}]] = true;
            }
        }
        else if (dir == 'S') {
            while (*(spies_x[xi].begin()) < yi) {
                int y = *(spies_x[xi].begin());
                spies_x[xi].erase(y);
                if (!elim[team[{xi, y}]]) curr.push_back(team[{xi, y}]);
                elim[team[{xi, y}]] = true;
            }
        }
        else if (dir == 'E') {
            while (*prev(spies_y[yi].end()) > xi) {
                int x = *prev(spies_y[yi].end());
                spies_y[yi].erase(x);
                if (!elim[team[{x, yi}]]) curr.push_back(team[{x, yi}]);
                elim[team[{x, yi}]] = true;
            }
        }
        else if (dir == 'W') {
            while (*(spies_y[yi].begin()) < xi) {
                int x = *(spies_y[yi].begin());
                spies_y[yi].erase(x);
                if (!elim[team[{x, yi}]]) curr.push_back(team[{x, yi}]);
                elim[team[{x, yi}]] = true;
            }
        }
        cout << curr.size() << " ";
        for (int i = curr.size() - 1; i >= 0; i--) cout << curr[i] << " ";
        cout << "\n";
    }

    return 0;
}