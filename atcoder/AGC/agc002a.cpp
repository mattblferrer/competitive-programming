#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll a, b;
    cin >> a >> b;
    if ((a <= 0) && (0 <= b)) cout << "Zero\n";
    else if (a > 0) cout << "Positive\n";
    else if (((b - a) % 2 == 0)) cout << "Negative\n";
    else cout << "Positive\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}