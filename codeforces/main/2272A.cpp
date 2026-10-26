#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void get_f(vector<ll> &a, vector<ll> &f) {
    int n = a.size();
    vector<ll> seen(n + 1);
    int curr = 0;
    for (ll i = 0; i < n; i++) {
        seen[a[i]] = true;
        for (ll j = curr; j <= n; j++) {
            if (seen[j]) curr++;
            else {
                f[i] = curr;
                break;
            }
        }
    }
}

void solve() {
    ll n, k;
    cin >> n >> k;
    ll p = n - k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> f(n);
    get_f(a, f);
    if (f[p] == p + 1) {
        cout << "-1\n";
        return;
    }

    ll max_f = f[p], i1 = -1, i2 = -1;
    for (ll x = 0; x < n; x++) {
        for (ll y = x + 1; y < n; y++) {
            f.clear();
            swap(a[x], a[y]);
            get_f(a, f);
            if (f[p] > max_f) {
                i1 = x, i2 = y;
                max_f = f[p];
            }
            swap(a[x], a[y]);
        }
    }
    if (i1 != -1) {
        cout << i1 + 1 << " " << i2 + 1 << "\n";
    }
    else cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}