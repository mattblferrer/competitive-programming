#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> x(n);
    set<ll> x_set;
    for (ll i = 0; i < n; i++) {
        cin >> x[i];
        x_set.insert(x[i]);
    }

    set<ll> best;
    for (ll i = 0; i < n; i++) {
        for (ll p = 0; p <= 32; p++) {
            set<ll> curr_set;
            curr_set.insert(x[i]);
            if (x_set.count(x[i] - (1 << p))) curr_set.insert(x[i] - (1 << p));
            if (x_set.count(x[i] + (1 << p))) curr_set.insert(x[i] + (1 << p));
            if (best.size() < curr_set.size()) best = curr_set;
        }
    }
    cout << best.size() << "\n";
    for (ll xi : best) cout << xi << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}