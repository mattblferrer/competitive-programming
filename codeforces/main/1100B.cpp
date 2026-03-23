#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<ll> cnt(n + 1);
    ll curr = 0;
    for (ll i = 0; i < m; i++) {
        ll ai;
        cin >> ai;
        if (cnt[ai] == 0) curr++;
        cnt[ai]++;
        if (curr == n) {
            cout << "1";
            curr = 0;
            for (ll j = 1; j <= n; j++) {
                cnt[j]--;
                if (cnt[j] > 0) curr++;
            }
        }
        else cout << "0";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}