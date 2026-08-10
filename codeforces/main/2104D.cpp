#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_prime(int n) {
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

vector<ll> sum_primes;

void precalc() {
    ll i = 2, sum = 0;
    while (sum_primes.size() < 400'000) {
        if (is_prime(i)) {
            sum += i;
            sum_primes.push_back(sum);
        }
        i++;
    }
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end(), greater<ll>());

    ll sum = 0, ans = n;
    for (ll i = 0; i < n; i++) {
        sum += a[i];
        if (sum >= sum_primes[i]) ans--;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    precalc();
    int t; cin >> t; while (t--) solve();
    return 0;
}