#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_valid(vector<ll>& perm) {
    for (ll i = 0; i < 5; i++) {
        if (perm[i] == 0 && perm[i + 1] == 1) return false;
        if (perm[i] == 1 && perm[i + 1] == 0) return false;
        if (perm[i] == 2 && perm[i + 1] == 3) return false;
        if (perm[i] == 3 && perm[i + 1] == 2) return false;
        if (perm[i] == 4 && perm[i + 1] == 5) return false;
        if (perm[i] == 5 && perm[i + 1] == 4) return false;
    }
    return true;
}

void solve() {
    vector<ll> d(6);
    ll maxk = 0;
    for (ll i = 0; i < 6; i++) cin >> d[i];
    vector<ll> perm = {0, 1, 2, 3, 4, 5};
    for (ll i = 0; i < 720; i++) {
        if (!is_valid(perm)) {
            next_permutation(perm.begin(), perm.end());
            continue;
        }
        ll curr = 0;
        for (ll j = 0; j < 6; j++) {
            curr += d[perm[j]] * powl(10, j);
            maxk = max(maxk, curr);
        }
        next_permutation(perm.begin(), perm.end());
    }
    cout << maxk;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}