#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    ll n = stoll(s.substr(0, s.size() - 2));
    if (n <= 200) cout << "SMALL\n";
    else if (n <= 500) cout << "MEDIUM\n";
    else cout << "LARGE\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}