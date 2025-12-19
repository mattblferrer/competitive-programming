#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    string s;
    cin >> n >> s;
    for (ll i = 0; i < n - 2; i++) {
        set<char> w;  // sliding window size 3
        w.insert(s[i]);
        w.insert(s[i + 1]);
        w.insert(s[i + 2]);
        if (w.size() == 3) {
            cout << "0\n";
            return;
        }
    }
    if (n == 1) cout << "2\n";
    else if (s[n - 2] == s[n - 1]) cout << "2\n";
    else cout << "1\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}