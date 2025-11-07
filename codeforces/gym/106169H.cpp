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
    vector<ll> loops, calc;
    loops.push_back(0);
    calc.push_back(0);
    for (ll i = 0; i < n; i++) {
        string word;
        cin >> word;
        ll k;
        if (word == "for") {
            cin >> k;
            loops.push_back(k);
            calc.push_back(0);
        }
        else if (word == "calc") {
            cin >> k;
            calc.back() = (calc.back() + k) % MOD;
        }
        else if (word == "end") {
            ll x = loops.back() * calc.back();
            loops.pop_back();
            calc.pop_back();
            calc.back() = (calc.back() + x) % MOD;
        }
    }
    cout << calc[0];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}