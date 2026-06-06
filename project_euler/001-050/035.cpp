#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<bool> is_prime;

void sieve(vector<bool>& is_prime, ll n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

bool is_circular(ll n) {
    string curr = to_string(n);
    for (ll i = 0; i < curr.size(); i++) {
        if (!is_prime[stoll(curr)]) return false;
        curr = curr.back() + curr;
        curr.pop_back();
    }
    return true;
}

void solve() {
    sieve(is_prime, 1000000);
    ll ans = 0;
    for (ll i = 0; i < 1000000; i++) {
        if (is_circular(i)) ans++;
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