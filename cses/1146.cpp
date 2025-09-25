#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

map<ll, ll> dp;
ll solve(ll n) {
    if (n == 0) return 0;
    if (dp.count(n)) return dp[n];
    if (n % 2 == 0) return dp[n] = solve(n / 2) + solve(n / 2 - 1) + n / 2;
    else return dp[n] = 2 * solve(n / 2) + n / 2 + 1;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    ll n;
    cin >> n;
    cout << solve(n);
    return 0;
}