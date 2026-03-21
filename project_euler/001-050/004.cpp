#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_palindrome(ll n) {
    string s = to_string(n);
    for (ll i = 0; i < s.size(); i++) {
        if (s[i] != s[s.size() - i - 1]) return false;
    }
    return true;
}

void solve() {
    ll ans = 0;
    for (ll i = 100; i <= 999; i++) {
        for (ll j = 100; j <= 999; j++) {
            if (is_palindrome(i * j)) ans = max(ans, i * j);
        }
    }
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}