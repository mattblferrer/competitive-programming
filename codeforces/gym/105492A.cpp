#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main() {
    ll n, m, r;
    cin >> n >> m >> r;
    r--;
    vector<queue<ll>> pending(n);
    vector<pair<ll, ll>> rank(n);
    ll p = 0;
    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (ll j = 0; j < m; j++) {
            if (s[j] == 'P') {
                pending[i].push(j);
                p++;
            }
        }
        rank[i] = {i, i};
    }
    for (ll k = 0; k < p; k++) {
        string s;
        cin >> s >> s;
        ll count = 0;
        bool ac = false;
        if (s[3] == 'y') {
            ll ind = 6;
            ac = true;
            while (true) {
                if (s[ind] == 'y') {
                    ind++;
                    count++;
                }
                else {
                    break;
                }
            }
        }
        sort(rank.rbegin(), rank.rend());
        ll curr = 0, oldCurr = 0;
        for (ll i = 0; i < n; i++) {
            if (pending[rank[i].second].size() > 0) {
                pending[rank[i].second].pop();
                oldCurr = rank[i].first;
                rank[i].first -= count;
                curr = i;
                break;
            }
        }
        if (!ac || count == 0) {
            continue;
        }
        ll newCurr = rank[curr].first;
        for (ll i = 0; i < n; i++) {
            if (curr == i) {
                continue;
            }
            else if (newCurr <= rank[i].first && oldCurr >= rank[i].first) {
                rank[i].first++;
            }
        }
    }
    for (ll i = 0; i < n; i++) {
        if (rank[i].second == r) {
            cout << rank[i].first + 1;
            break;
        }
    }
}