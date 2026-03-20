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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        if (a[i] == 25) cnt[25]++;
        else if (a[i] == 50) {
            cnt[50]++;
            cnt[25]--;
        }
        else {
            cnt[100]++;
            if (cnt[50] > 0) {
                cnt[50]--;
                cnt[25]--;
            }
            else {
                cnt[25] -= 3;
            }
        }
        if ((cnt[25] < 0) || (cnt[50] < 0)) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}