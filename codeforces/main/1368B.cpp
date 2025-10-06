#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll k;
    cin >> k;
    string og = "codeforces";
    ll curr = 1, ctr = 0;
    vector<ll> freq(10, 1);
    while (curr < k) {
        freq[ctr]++;
        ctr = (ctr + 1) % 10;
        curr = 1;
        for (ll i = 0; i < 10; i++) curr *= freq[i];
    }
    for (ll i = 0; i < 10; i++) {
        for (ll j = 0; j < freq[i]; j++) cout << og[i];
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}