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
    vector<ll> x(n);
    for (ll i = 0; i < n; i++) cin >> x[i];

    map<ll, ll> cnt;
    for (ll i = 0; i < k; i++) cnt[x[i]]++;
    cout << cnt.size() << " ";

    for (ll i = k; i < n; i++) {
        cnt[x[i - k]]--;
        cnt[x[i]]++;
        if (cnt[x[i - k]] == 0) cnt.erase(x[i - k]);
        cout << cnt.size() << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}