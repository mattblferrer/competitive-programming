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
    vector<ll> cnt(3);
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        cnt[ai]++;
    }
    for (ll i = 0; i < min(cnt[2], 1LL); i++) cout << "2 ";
    for (ll i = 0; i < min(cnt[1], 1LL); i++) cout << "1 ";
    for (ll i = 0; i < cnt[2] - 1; i++) cout << "2 ";
    for (ll i = 0; i < n - cnt[2] - min(cnt[1], 1LL); i++) cout << "1 ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}