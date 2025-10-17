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
    vector<int> p;
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') p.push_back(i);
    }
    cout << p.size() << "\n";
    for (int i = 0; i < p.size(); i++) {
        cout << p[i] + 1 << " ";
    }
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}