#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

ll brute(vector<ll> d, ll n, ll k) {
    ll ans = INF;
    ll min_i = 0;
    for (int i = 0; i < (1 << n); i++) {
        if (__builtin_popcount(i) != k) continue;
        if (((1 << (n - 1)) & i) == 0) continue;
        vector<bool> used(n);
        ll curr = 0, high = n - 1;
        for (int j = 0; j < n; j++) {
            if ((1 << j) & i) used[j] = true;
        }
        for (ll j = n - 1; j >= 0; j--) {
            if (used[j]) high = j;
            curr += (d[high] - d[j]) * (d[high] - d[j]);
        }
        if (ans > curr) {
            ans = curr;
            min_i = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if ((1 << i) & min_i) cout << d[i] << " ";
    }
    return ans;
}

void solve() {
    ll n, k, di;
    cin >> n >> k;
    vector<ll> d(n), d_orig(n);

    for (ll i = 0; i < n; i++) {
        cin >> di;
        d[i] = di;
        d_orig[i] = di;
    }
    sort(d.begin(), d.end());
    cout << "brute: " << brute(d, n, k) << "\n";
    ll cost = 0;
    for (ll i = 0; i < n - 1; i++) {
        cost += (d[n - 1] - d[i]) * (d[n - 1] - d[i]);
    }   
    vector<bool> used(n, false);
    used[n - 1] = true;
    ll k_opt = cost, k_idx = 0;
    for (ll kc = 0; kc < k - 1; kc++) {
        for (ll i = 0; i < n; i++) {
            if (used[i]) continue;
            ll high = INF, curr = 0;
            used[i] = true;
            for (ll j = n - 1; j >= 0; j--) {
                if (used[j]) high = j;
                curr += (d[high] - d[j]) * (d[high] - d[j]);
            }
            used[i] = false;
            cout << i << " " << curr << "\n";
            if (curr <= k_opt) {
                k_opt = curr;
                k_idx = i;
            }
        }   
        used[k_idx] = true;
    }
    cout << "penalty: " << k_opt << "\n";
    vector<ll> days;
    for (ll i = 0; i < n; i++) {
        if (used[i]) days.push_back(d[i]);
    }
    for (ll i = 0; i < n; i++) {
        cout << *lower_bound(days.begin(), days.end(), d_orig[i]) << " ";
    }

    // TODO: solve
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}