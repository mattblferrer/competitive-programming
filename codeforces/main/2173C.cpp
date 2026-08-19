#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    set<ll> a_queue(a.begin(), a.end()), a_set(a.begin(), a.end()), a_match;

    vector<ll> b;
    while (!a_queue.empty()) {
        if (a_match.size() == a_set.size()) break;

        ll a0 = *a_queue.begin();
        for (ll j = a0; j <= k; j += a0) {
            if (a_set.count(j) == 0) {
                cout << "-1\n";
                return;
            }
        }
        b.push_back(a0);
        for (ll j = a0; j <= k; j += a0) {
            a_match.insert(j);
            a_queue.erase(j);
        }

    }

    cout << b.size() << "\n";
    for (ll i = 0; i < b.size(); i++) cout << b[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}