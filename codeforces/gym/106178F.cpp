#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

map<ll, ll> factorize(ll n) {
    map<ll, ll> factors;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int cnt = 0;
            while (n % i == 0) {
                cnt++;
                n /= i;
            }
            factors[i] = cnt;
        }
    }
    if (n != 1) factors[n] = 1;
    return factors;
}

void solve() {
    string x;
    cin >> x;
    ll first11 = stoll(x.substr(0, 11));
    map<ll, ll> factors = factorize(first11);
    factors[2] += max(0, (int)x.size() - 11);
    factors[5] += max(0, (int)x.size() - 11);

    int sz = factors.size();
    for (auto &pair : factors) {
        if (pair.second == 0) sz--;
    }
    cout << sz << "\n";
    for (auto &pair : factors) {
        if (pair.second != 0) cout << pair.first << " " << pair.second << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}