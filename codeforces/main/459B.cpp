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
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        ll ai;
        cin >> ai;
        cnt[ai]++;
    }
    ll high = cnt.rbegin()->first, low = cnt.begin()->first;
    ll diff = high - low;
    if (diff == 0) cout << diff << " " << cnt[high]*(cnt[high] - 1)/2;
    else cout << diff << " " << cnt[high]*cnt[low];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}