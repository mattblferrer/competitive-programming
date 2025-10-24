#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ll n, k;
vector<ll> d;          // 1-indexed sorted d
vector<ll> p1, p2;     // prefix sums (1-indexed)

ll cost(ll l, ll r) {
    if (l > r) return 0;
    ll cnt = r - l + 1;
    ll dr = d[r];
    ll sum = p1[r] - p1[l - 1];
    ll sum2 = p2[r] - p2[l - 1];
    return cnt * dr * dr - 2 * dr * sum + sum2;
}

void compute_dc(const vector<ll>& dp_prev, vector<ll>& dp_curr, vector<ll>& opt_row,
                ll L, ll R, ll optL, ll optR) {
    if (L > R) return;
    ll mid = (L + R) >> 1;
    pll best = {INF, -1};
    ll start = max(optL, 0LL);
    ll end = min(optR, mid - 1);
    for (ll j = start; j <= end; j++) {
        ll val = dp_prev[j] + cost(j + 1, mid);
        if (val < best.first) {
            best = {val, j};
        }
    }
    dp_curr[mid] = best.first;
    opt_row[mid] = best.second;
    if (L <= mid - 1) compute_dc(dp_prev, dp_curr, opt_row, L, mid - 1, optL, best.second);
    if (mid + 1 <= R) compute_dc(dp_prev, dp_curr, opt_row, mid + 1, R, best.second, optR);
}

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<pll> arr(n);
    for (ll i = 0; i < n; i++) arr[i] = {a[i], i};
    sort(arr.begin(), arr.end());

    d.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) d[i] = arr[i - 1].first;

    p1.assign(n + 1, 0);
    p2.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) {
        p1[i] = p1[i - 1] + d[i];
        p2[i] = p2[i - 1] + d[i] * d[i];
    }
    k = min(k, n);

    vector<ll> dp_prev(n + 1, INF), dp_curr(n + 1, INF);
    vector<vector<ll>> opt(k + 1, vector<ll>(n + 1, -1));
    dp_prev[0] = 0;
    for (ll i = 1; i <= n; i++) {
        dp_prev[i] = cost(1, i);
        opt[1][i] = 0;
    }

    vector<vector<ll>> dp_all(k + 1, vector<ll>(n + 1, INF));
    dp_all[1] = dp_prev;
    for (ll g = 2; g <= k; g++) {
        dp_curr.assign(n + 1, INF);
        vector<ll> opt_row(n + 1, -1);
        compute_dc(dp_prev, dp_curr, opt_row, 1, n, 0, n-1);
        for (ll i = 1; i <= n; i++) opt[g][i] = opt_row[i];
        dp_all[g] = dp_curr;
        dp_prev.swap(dp_curr);
    }

    ll best = INF;
    ll bestg = 1;
    for (ll g = 1; g <= k; g++) {
        if (dp_all[g][n] < best) {
            best = dp_all[g][n];
            bestg = g;
        }
    }
    vector<ll> day_idx(n, -1);
    ll curr_n = n, g = bestg;
    while (g > 0) {
        ll j = opt[g][curr_n];
        ll l = j + 1, r = curr_n;
        for (ll t = l; t <= r; t++) day_idx[t - 1] = r;
        curr_n = j;
        g--;
    }

    vector<ll> ans(n);
    for (ll pos = 1; pos <= n; pos++) {
        ll og = arr[pos - 1].second;
        ll r = day_idx[pos - 1];
        ans[og] = d[r];
    }
    for (ll i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}
