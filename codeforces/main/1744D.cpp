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
    vector<ll> a(n);
    ll curr = 0;
    priority_queue<pll> pq;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        while (a[i] % 2 == 0) {
            curr++;
            a[i] /= 2;
        }
        ll texp = 0, temp = i + 1;
        while (temp % 2 == 0) {
            texp++;
            temp /= 2;
        }
        pq.push({texp, i});
    }
    ll ans = 0;
    while (curr < n) {
        if (pq.empty()) break;
        auto pair = pq.top();
        ll exp = pair.first;
        pq.pop();
        curr += exp;
        ans++;
    }
    if (curr < n) cout << "-1\n";
    else cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}