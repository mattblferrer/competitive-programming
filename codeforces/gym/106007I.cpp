#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k;
    cin >> n >> k;
    deque<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    bool rev = false;
    for (ll i = 0; i < k; i++) {
        if (rev) a.pop_back();
        else a.pop_front();
        rev = 1 - rev;
    }
    if (rev) {
        for (ll i = a.size() - 1; i >= 0; i--) cout << a[i] << " ";
    }
    else {
        for (ll i = 0; i < a.size(); i++) cout << a[i] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}