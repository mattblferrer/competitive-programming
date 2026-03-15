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
    set<ll> a;
    vector<ll> a_arr(n);
    for (ll i = 0; i < n; i++) {
        cin >> a_arr[i];
        a.insert(a_arr[i]);
    }
    sort(a_arr.begin(), a_arr.end());
    ll min_d = INF;
    for (ll i = 0; i < n - 1; i++) {
        min_d = min(min_d, a_arr[i + 1] - a_arr[i]);
    }
    ll cnt = 0;
    for (ll ai: a) {
        cnt += a.count(ai - min_d) + a.count(ai + min_d);
    }
    cnt /= 2;
    cout << min_d << " " << cnt;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}