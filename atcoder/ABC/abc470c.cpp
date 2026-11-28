#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<int> a(n);
    set<int> idx;
    ll ans = 0;

    for (ll i = 0; i < q; i++) {
        ll type;
        cin >> type;
        if (type == 1) {
            ll x;
            cin >> x;
            x--;
            if (a[x] == 0) idx.insert(x);
            ans ^= a[x] ^ (a[x] + 1);
            a[x]++;
        }
        else if (type == 2) {
            set<int> new_idx;
            for (ll x : idx) {
                ans ^= a[x] ^ (a[x] - 1);
                a[x]--;
                if (a[x] != 0) new_idx.insert(x);
            }
            idx = new_idx;
        }

        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}