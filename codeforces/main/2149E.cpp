#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<ll> a(n + 1);
    for (ll i = 0; i < n; i++) cin >> a[i];
    a[n] = INF;
    ll ans = 0;
    ll rh = -1, rl = -1;
    map<ll, ll> sh, sl;
    for (ll i = 0; i < n; i++) {
        if (sl.size() < k) {
            while (sl.size() < k) {
                bool step = false;
                if (rl < n) {
                    rl++;     
                    sl[a[rl]]++;
                    step = true;
                }
                if (!step) break;
            }
        }
        if (sh.size() < k + 1) {
            while (sh.size() < k + 1) {
                bool step = false;
                if (rh < n) {
                    rh++;
                    sh[a[rh]]++;
                    step = true;
                }
                if (!step) break;
            }
        }
        ans += max(0LL, min(rh - 1, i + r - 1) - max(rl, i + l - 1) + 1);
        sh[a[i]]--;
        sl[a[i]]--;
        if (sh[a[i]] == 0) sh.erase(a[i]);
        if (sl[a[i]] == 0) sl.erase(a[i]);
        
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}