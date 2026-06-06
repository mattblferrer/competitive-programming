#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool satisfied(ll n) {
    string base10 = to_string(n);
    string base2 = "";
    while (n > 0) {
        if (n & 1) base2 += '1';
        else base2 += '0';
        n /= 2;
    }
    reverse(base2.begin(), base2.end());
    ll len10 = base10.size(), len2 = base2.size();
    for (ll i = 0; i * 2 <= len10; i++) {
        if (base10[i] != base10[len10 - i - 1]) return false;
    }
    for (ll i = 0; i * 2 <= len2; i++) {
        if (base2[i] != base2[len2 - i - 1]) return false;
    }
    return true;
}

void solve() {
    ll ans = 0;
    for (ll i = 1; i < 1000000; i++) {
        if (satisfied(i)) ans += i;
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