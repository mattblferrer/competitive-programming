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
    string s;
    cin >> s;

    ll xor0 = 0, xor1 = 0;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '0') xor0 ^= a[i];
        else xor1 ^= a[i];
    }
    vector<ll> pref(n + 1);
    pref[0] = a[0];
    for (ll i = 1; i <= n; i++) pref[i] = pref[i - 1] ^ a[i - 1];

    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll l, r;
            cin >> l >> r;
            l--; r--;

            xor0 ^= pref[r + 1] ^ pref[l];
            xor1 ^= pref[r + 1] ^ pref[l];
        }
        else if (type == 2) {
            ll g;
            cin >> g;

            if (g == 0) cout << xor0 << " ";
            else cout << xor1 << " ";
        }
        else cerr << "invalid type\n";
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