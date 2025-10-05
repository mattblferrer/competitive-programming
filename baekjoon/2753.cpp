#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

int solve() {
    int n;
    cin >> n;
    if (n % 400 == 0) return 1;
    else if (n % 100 == 0) return 0;
    else if (n % 4 == 0) return 1;
    else return 0;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    cout << solve();
    return 0;
}