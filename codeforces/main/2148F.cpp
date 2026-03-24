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
    vector<deque<ll>> a(n);
    ll max_k = 0;
    for (ll i = 0; i < n; i++) {
        ll k;
        cin >> k;
        max_k = max(max_k, k);
        a[i].assign(k, 0);
        for (ll j = 0; j < k; j++) cin >> a[i][j];
    }
    sort(a.begin(), a.end(), [](deque<ll> va, deque<ll> vb) {
        return va.size() > vb.size();
    });

    ll start = 0;
    deque<ll> ans;
    while (a.size() > 0) {
        deque<ll> min_a = {INF};
        for (ll i = 0; i < a.size(); i++) {
            bool equal = true;
            for (ll j = 0; j < min(min_a.size(), a[i].size()); j++) {
                if (min_a[j] > a[i][j]) {
                    min_a = a[i];
                    equal = false;
                    break;
                }
                else if (min_a[j] < a[i][j]) {
                    equal = false;
                    break;
                }
            }
            if (equal) min_a = a[i];
        }
        ans.insert(ans.end(), min_a.begin(), min_a.end());

        while ((a.size() > 0) && (min_a.size() >= a.back().size())) a.pop_back();
        for (ll i = 0; i < a.size(); i++) {
            for (ll j = 0; j < min_a.size(); j++) a[i].pop_front();
        }
    }

    for (ll i = 0; i < max_k; i++) cout << ans[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}