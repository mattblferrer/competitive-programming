#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string n;
    ll j, k;
    cin >> n >> j >> k;
    string perm_j = n, perm_k = n;
    for (ll i = 0; i < j - 1; i++) next_permutation(perm_j.begin(), perm_j.end());
    for (ll i = 0; i < k - 1; i++) next_permutation(perm_k.begin(), perm_k.end());
    ll x = 0, y = 0;
    vector<bool> check(n.size());
    for (ll i = 0; i < n.size(); i++) {
        if (perm_j[i] == perm_k[i]) {
            x++;
            check[i] = true;
        }
    }
    map<ll, ll> cnt_j, cnt_k;
    for (ll i = 0; i < n.size(); i++) {
        if (check[i]) continue;
        cnt_j[perm_j[i]]++;
        cnt_k[perm_k[i]]++;
    }
    for (const auto& pair: cnt_j) {
        ll fi = pair.first;
        y += min(cnt_j[fi], cnt_k[fi]);
    }
    for (const auto& pair: cnt_k) {
        ll fi = pair.first;
        y += min(cnt_j[fi], cnt_k[fi]);
    }
    y /= 2;
    cout << x << "A" << y << "B" << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}