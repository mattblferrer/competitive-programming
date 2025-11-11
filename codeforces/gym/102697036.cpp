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
    map<string, ll> sl;
    for (ll i = 0; i < n; i++) {
        string s;
        ll k;
        cin >> s >> k;
        sl[s] = k;
    }
    ll t;
    cin >> t;
    for (ll i = 0; i < t; i++) {
        string s;
        cin >> s;
        cout << sl[s] << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}