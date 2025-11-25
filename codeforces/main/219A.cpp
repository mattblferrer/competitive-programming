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
    string s;
    cin >> k >> s;
    map<char, ll> cnt;
    ll n = s.size();
    for (ll i = 0; i < n; i++) {
        cnt[s[i]]++;
    }
    ll g = cnt.begin()->second;
    for (const auto& pair: cnt) {
        g = gcd(g, pair.second); 
    }
    if (g % k != 0) {
        cout << -1;
        return;
    }
    for (auto pair: cnt) {
        cnt[pair.first] /= k;
    }
    for (ll i = 0; i < k; i++) {
        for (auto pair: cnt) {
            for (ll j = 0; j < pair.second; j++) cout << pair.first;
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}