#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n = 100;
    ll sum_sq = 0, sum = 0, sq_sum = 0;
    for (ll i = 1; i <= 100; i++) {
        sum += i;
        sum_sq += i*i;
    }
    sq_sum = sum*sum;
    cout << abs(sum_sq - sq_sum);
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}