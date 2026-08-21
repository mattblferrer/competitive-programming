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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    ll pos = 0, neg = 0, zeros = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] > 0) pos++;
        else if (a[i] < 0) neg++;
        else zeros++;
    }
    if ((pos > 2) || (neg > 2)) { cout << "NO\n"; return; }
    ll curr = 0;
    vector<ll> b;
    for (ll i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (curr == 2) continue;
            curr++;
        }
        b.push_back(a[i]);
    }
    if (b.size() < 3) { cout << "YES\n"; return; }
    set<ll> b_set(b.begin(), b.end());

    for (ll i = 0; i < b.size(); i++) {
        for (ll j = i + 1; j < b.size(); j++) {
            for (ll k = j + 1; k < b.size(); k++) {
                if (b_set.count(b[i] + b[j] + b[k]) == 0) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}