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

    vector<ll> a6, a3, a2, an;
    for (ll i = 0; i < n; i++) {
        if (a[i] % 6 == 0) a6.push_back(a[i]);
        else if (a[i] % 3 == 0) a3.push_back(a[i]);
        else if (a[i] % 2 == 0) a2.push_back(a[i]);
        else an.push_back(a[i]);
    }
    for (ll ai : a6) cout << ai << " ";
    if (a3.size() < a2.size()) {
        for (ll ai : a3) cout << ai << " ";
        for (ll ai : an) cout << ai << " ";
        for (ll ai : a2) cout << ai << " ";
    }
    else {
        for (ll ai : a2) cout << ai << " ";
        for (ll ai : an) cout << ai << " ";
        for (ll ai : a3) cout << ai << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}