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
    ll digit_sum = 0;
    for (int i = 0; i < s.size(); i++)
    {
        digit_sum += s[i] - '0';
    }

    if (digit_sum % 9 == 0) cout << "Yes";
    else cout << "No";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    for (int i = 0; i < t; i++)
    {
        solve();
        cout << "\n";
    }
    return 0;
}