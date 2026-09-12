#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

ll cyclic_shift(ll n, ll x) {
    string to_str = to_string(n);
    ll m = to_str.size();
    x %= m;
    deque<char> dq(to_str.begin(), to_str.end());
    for (int i = 0; i < x; i++) {
        dq.push_front(dq.back());
        dq.pop_back();
    }
    string res(dq.begin(), dq.end());
    return stoll(res);
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> ans;
    string to_str = to_string(n);
    ll k = to_str.size();
    for (ll x = 1; x < k; x++) {
        ll c = cyclic_shift(n, x);
        if (c < n) continue;
        ll d = c - n;
        if ((d % k) == x) ans.push_back(d);
    }
    sort(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}