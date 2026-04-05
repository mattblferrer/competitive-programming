#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> perm = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (ll i = 0; i < 999999; i++) {
        next_permutation(perm.begin(), perm.end());
    }
    for (ll i = 0; i < 10; i++) cout << perm[i];
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}