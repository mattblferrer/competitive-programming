#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_prime(ll n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    ll start = 0;
    if (n % 2 == 1) {
        a[0] = 2;
        start++;
    }
    
    ll p = 2;
    for (ll i = start; i < n; i += 2) {
        a[i] = p*p;
        p++;
        while (!is_prime(p)) p++;
        a[i + 1] = a[i]*p;
    }

    for (ll i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}