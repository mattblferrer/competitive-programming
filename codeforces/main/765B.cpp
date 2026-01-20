#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    char curr = 'a';
    if (s[0] != 'a') {
        cout << "NO\n";
        return;
    }
    for (ll i = 0; i < n; i++) {
        if (s[i] > curr + 1) {
            cout << "NO\n";
            return;
        }
        curr = max(curr, s[i]);
    }
    cout << "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}