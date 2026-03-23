#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    map<ll, vector<ll>> pos;
    for (ll i = 0; i < n; i++) {
        pos[a[i]].push_back(i);
    }
    for (const auto& pair: pos) {
        if (pair.second.size() % k != 0) {
            cout << "0\n";
            return;
        }
    }
    ll ans = 0, left = 0;
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        cnt[a[i]]++;
        while (cnt[a[i]] > pos[a[i]].size() / k) {
            cnt[a[left]]--;
            left++;
        }
        ans += i - left + 1;
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