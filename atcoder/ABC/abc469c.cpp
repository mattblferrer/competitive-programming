#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    string s;
    cin >> s;
    ll curr = 0, hit = 0, line = 0;
    while (line < n) {
        if (s[curr] == 'o') hit++;
        while (hit) {
            curr++;
            if (curr == n) { curr--; break; }
            if (s[curr] == 'x') hit--;
        }
        cout << curr + 1 << "\n";
        line++;
        curr = min(curr + 1, n - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}