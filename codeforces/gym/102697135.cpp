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
    cin >> n;
    vector<string> w(n);
    for (ll i = 0; i < n; i++) {
        cin >> w[i];
    }
    sort(w.begin(), w.end());
    reverse(w.begin(), w.end());
    for (string s: w) {
        cout << s << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}