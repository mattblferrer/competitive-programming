#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string s;
    cin >> s;
    vector<ll> dirs(4);
    string dstr = "NSEW";
    for (ll i = 0; i < s.size(); i++) {
        for (ll j = 0; j < 4; j++) {
            if (s[i] == dstr[j]) dirs[j]++;
        }
    }
    if (((dirs[0] == 0) != (dirs[1] == 0)) || ((dirs[2] == 0) != (dirs[3] == 0))) {
        cout << "No\n";
    }
    else cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}