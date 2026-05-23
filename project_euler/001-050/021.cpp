#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

int sum_proper_divisors(int n) {
    int ans = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans += i;
            if (n / i != i) ans += n / i;
        }
    }
    return ans;
}

bool is_amicable(int n) {
    int sd = sum_proper_divisors(n);
    return ((sd != n) && (sum_proper_divisors(sd) == n));
}

void solve() {
    int ans = 0;
    for (int i = 1; i <= 10000; i++) {
        if (is_amicable(i)) {
            ans += i;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}