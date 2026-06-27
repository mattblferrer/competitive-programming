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
    if (n == 1) {
        cout << "1 0";
        return;
    }

    map<ll, ll> fac;
    for (ll i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            fac[i]++;
            n /= i;
        }
    }
    if (n != 1) fac[n]++;
    ll min_n = 1, min_exp = INF, max_exp = 0;
    for (const auto &pair : fac) {
        min_n *= pair.first;
        min_exp = min(min_exp, pair.second);
        max_exp = max(max_exp, pair.second);
    }
    if ((min_exp == max_exp) && ((max_exp & (max_exp - 1)) == 0)) cout << min_n << " " << ceil(log2(max_exp));
    else cout << min_n << " " << 1 + ceil(log2(max_exp));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}