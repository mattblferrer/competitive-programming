#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> target(n);
    for (int i = 0; i < n; i++) {
        cin >> target[i];
    }

    int k = 0;
    vector<int> rows(n), suff(n + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (target[i][j] == '0') continue;
            k++;
            rows[i]++;
        }
    }
    suff[n - 1] = rows[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suff[i] = suff[i + 1] + rows[i];
    }

    cout << k << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (target[i][j] == '0') continue;
            cout << (i + 1) << " " << (j - suff[i + 1] + (2000 * m)) % m + 1 << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
    }
    return 0;
}