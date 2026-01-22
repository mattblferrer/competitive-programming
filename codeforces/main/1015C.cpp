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
    vector<pll> songs(n);
    ll curr = 0;
    for (ll i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        songs[i] = {a, b};
        curr += a;
    }
    sort(songs.begin(), songs.end(), [](pll a, pll b){
        return a.first - a.second > b.first - b.second;
    });
    for (ll i = 0; i < n; i++) {
        if (curr <= m) {
            cout << i;
            return;
        }
        curr = curr - songs[i].first + songs[i].second;
    }
    if (curr <= m) cout << n;
    else cout << -1;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}