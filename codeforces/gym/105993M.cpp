#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> b(n);
    set<int> thief_set;

    // if first is liar, decreasing
    b = a;
    bool inc = false;
    int thief = -1, lies = 1;
    b[0] = b[1] + 1;
    for (int i = 0; i < n - 1; i++) {
        if (b[i] == 0) inc = true;
        if ((!inc) && (b[i] - b[i + 1] != 1)) {
            lies++;
            b[i + 1] = b[i] - 1;
        }
        if ((inc) && (b[i] - b[i + 1] != -1)) {
            lies++;
            b[i + 1] = b[i] + 1;
        }
    }
    if (lies == 1) {
        for (int i = 0; i < n; i++) {
            if (b[i] == 0) thief = i + 1;
        }
        if (thief != -1) thief_set.insert(thief);
    }

    // if first is liar, increasing
    if (a[1] == 1) {
        b = a;
        inc = true;
        thief = -1, lies = 1;
        b[0] = b[1] - 1;
        for (int i = 0; i < n - 1; i++) {
            if (b[i] == 0) inc = true;
            if ((!inc) && (b[i] - b[i + 1] != 1)) {
                lies++;
                b[i + 1] = b[i] - 1;
            }
            if ((inc) && (b[i] - b[i + 1] != -1)) {
                lies++;
                b[i + 1] = b[i] + 1;
            }
        }
        if (lies == 1) {
            for (int i = 0; i < n; i++) {
                if (b[i] == 0) thief = i + 1;
            }
            if (thief != -1) thief_set.insert(thief);
        }
    }

    // if first is not liar
    b = a;
    inc = false;
    thief = -1, lies = 0;
    for (int i = 0; i < n - 1; i++) {
        if (b[i] == 0) inc = true;
        if ((!inc) && (b[i] - b[i + 1] != 1)) {
            lies++;
            b[i + 1] = b[i] - 1;
        }
        if ((inc) && (b[i] - b[i + 1] != -1)) {
            lies++;
            b[i + 1] = b[i] + 1;
        }
    }
    if (lies == 1) {
        for (int i = 0; i < n; i++) {
            if (b[i] == 0) thief = i + 1;
        }
        if (thief != -1) thief_set.insert(thief);
    }
    if (thief_set.size() > 1) cout << "-1";
    else cout << *thief_set.begin();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
        cout << "\n";
    }
    return 0;
}