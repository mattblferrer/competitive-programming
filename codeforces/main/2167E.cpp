#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, k, x;
    cin >> n >> k >> x;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    a.push_back(-1e10);
    a.push_back(1e10);
    sort(a.begin(), a.end());
    n += 2;

    ll left = -1, right = 1e10 + 1;
    while (right - left > 1) {
        ll time = (left + right) / 2;
        ll curr_k = 0;
        a[0] = -time;
        a[n - 1] = x + time;

        for (ll i = 1; i < n; i++) {
            curr_k += max(0LL, (a[i] - time) - (a[i - 1] + time) + 1);
        }
        if (curr_k >= k) left = time;
        else right = time;
    }
    set<ll> ans;
    a[0] = -left;
    a[n - 1] = x + left;
    for (ll i = 1; i < n; i++) {
        for (ll j = a[i - 1] + left; j <= a[i] - left; j++) {
            ans.insert(j);
            if (ans.size() == k) break;
        }
        if (ans.size() == k) break;
    }
    for (ll ai : ans) cout << ai << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}