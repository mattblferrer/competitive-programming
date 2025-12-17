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
    vector<ll> a(9);
    ll p = 1;
    for (ll i = 0; i < 7; i++) {
        for (ll j = 0; j < (n / p) % 10; j++) {
            a[j] += p;
        }
        p *= 10;
    }
    ll k = 0;
    for (ll i = 0; i < 9; i++) {
        if (a[i] != 0) k++;
    }
    cout << k << "\n";
    for (ll i = 0; i < k; i++) cout << a[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}