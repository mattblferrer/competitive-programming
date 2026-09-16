#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string nstr;
    cin >> nstr;
    vector<ll> cnt(10);
    ll rem = 0;
    for (char d: nstr) {
        cnt[d - '0']++;
        rem = (rem + d - '0') % 9;
    }
    if (rem == 0) {
        cout << "YES\n";
        return;
    }
    
    ll need = 9 - rem;
    if (need % 2 == 1) need += 9;
    while ((cnt[3] > 0) && (need >= 6)) {
        need -= 6;
        cnt[3]--;
    }
    while ((cnt[2] > 0) && (need >= 2)) {
        need -= 2;
        cnt[2]--;
    }
    if (need == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}