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
    if (n == 1) cout << "walk";
    else if (n == 2) cout << "No";
    else if (n == 3) cout << "No";
    else if (n == 4) cout << "No";
    else if (n == 5) cout << "Yes";
    else if (n == 6) cout << "Yes";
    else if (n == 7) cout << "backwards";
    else if (n == 8) cout << "seven";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}