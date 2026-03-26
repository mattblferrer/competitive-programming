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
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) cin >> b[i];
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) cnt[b[i]]++;
    map<ll, ll> xt, mapping;
    vector<ll> a(n);

    ll curr = 1;
    for (ll i = 0; i < n; i++) {
        if (mapping.count(b[i]) == 0) {
            mapping[b[i]] = curr;
            curr++;
        }
        if (xt[b[i]] >= b[i]) {
            mapping[b[i]] = curr;
            curr++;
            xt[b[i]] = 0;
        }
        a[i] = mapping[b[i]];
        xt[b[i]]++;
    }
    map<ll, ll> cnt_check;
    for (ll i = 0; i < n; i++) cnt_check[a[i]]++;
    for (ll i = 0; i < n; i++) {
        if (cnt_check[a[i]] != b[i]) {
            cout << "-1\n";
            return;
        }
    }
    for (ll i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}