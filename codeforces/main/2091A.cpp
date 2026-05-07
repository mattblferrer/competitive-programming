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
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> cnt(10);
    string ref_str = "01032025";
    vector<ll> ref(10);
    for (ll i = 0; i < ref_str.size(); i++) ref[ref_str[i] - '0']++;
    for (ll i = 0; i < n; i++) {
        cnt[a[i]]++;
        bool valid = true;
        for (ll j = 0; j < 10; j++) {
            if (cnt[j] < ref[j]) valid = false;
        }
        if (valid) {
            cout << i + 1 << '\n';
            return;
        }
    }
    cout << "0\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}