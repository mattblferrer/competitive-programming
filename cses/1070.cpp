#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    if (n == 1) cout << "1";
    else if (n < 4) cout << "NO SOLUTION";
    else {
        for (int i = 2; i <= n - n % 2; i += 2) cout << i << " ";
        for (int i = 1; i <= n - (1 - n % 2); i += 2) cout << i << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}