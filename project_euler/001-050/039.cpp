#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> sol(1001);
    for (ll a = 1; a <= 500; a++) {
        for (ll b = a; b <= 500; b++) {
            ll c2 = a * a + b * b;
            ll c = sqrt(c2);
            if ((c * c == c2) && (a + b + c <= 1000)) sol[a + b + c]++;
        }
    }
    ll ans = 0, max_sol = 0;
    for (ll i = 0; i <= 1000; i++) {
        if (sol[i] > max_sol) {
            ans = i;
            max_sol = sol[i];
        }
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