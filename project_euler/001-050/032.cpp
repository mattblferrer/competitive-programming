#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_pandigital_product(ll a, ll b, ll prod) {
    string as = to_string(a);
    string bs = to_string(b);
    string prods = to_string(prod);
    string total = as + bs + prods;
    if (total.size() != 9) return false;
    sort(total.begin(), total.end());
    return total == "123456789";
}

void solve() {
    ll ans = 0;
    set<ll> valid;
    for (ll i = 1; i <= 9999; i++) {
        for (ll j = 1; j <= 9999; j++) {
            ll prod = i * j;
            if (is_pandigital_product(i, j, prod)) valid.insert(prod);
        }
    }
    for (ll k : valid) ans += k;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}