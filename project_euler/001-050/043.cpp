#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool property_satisfied(ll n) {
    vector<ll> primes = {2, 3, 5, 7, 11, 13, 17};
    string nstr = to_string(n);
    for (ll i = 1; i < 8; i++) {
        ll sub = stoll(nstr.substr(i, 3));
        if (sub % primes[i - 1] != 0) return false;
    }
    return true;
}

void solve() {
    string currstr = "1023456789";
    ll ans = 0;
    do {
        ll curr = stoll(currstr);
        if (property_satisfied(curr)) ans += curr;
    } while (next_permutation(currstr.begin(), currstr.end()));
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}