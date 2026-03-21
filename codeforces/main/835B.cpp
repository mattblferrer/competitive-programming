#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll k;
    string n;
    cin >> k >> n;
    vector<ll> cnt(10);
    ll sum = 0;
    for (ll i = 0; i < n.size(); i++) {
        cnt[n[i] - '0']++;
        sum += n[i] - '0';
    }
    ll ans = 0;
    while (sum < k) {
        for (ll i = 0; i < 10; i++) {
            if (cnt[i] > 0) {
                sum += 9 - i;
                cnt[i]--;
                ans++;
                break;
            }
        }
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}