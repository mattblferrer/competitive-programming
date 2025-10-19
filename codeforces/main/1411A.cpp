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
    string s;
    cin >> s;
    int b = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == ')') b++;
        else break;
    }
    if (b > n / 2) cout << "Yes\n";
    else cout << "No\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}