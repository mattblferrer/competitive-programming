#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<ll> powers;
    map<ll, ll> cnt;
    ll curr = 1;
    while (curr <= 1e16) {
        powers.push_back(curr);
        curr *= k;
    }
    for (ll i = 0; i < n; i++) {
        for (ll j = powers.size() - 1; j >= 0; j--) {
            curr = a[i] / powers[j];
            cnt[powers[j]] += curr;
            a[i] -= curr * powers[j];
        }
    }
    for (const auto& pair: cnt) {
        if (pair.second > 1) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}