#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m;
    cin >> n >> m;
    map<string, string> m1, m2;
    for (ll i = 0; i < m; i++) {
        string a, b;
        cin >> a >> b;
        m1[a] = b;
        m2[b] = a;
    }
    for (ll i = 0; i < n; i++) {
        string ci;
        cin >> ci;
        
        string trans;
        if (m1.count(ci)) trans = m1[ci];
        else trans = m2[ci];
        if (ci.size() > trans.size()) cout << trans << " ";
        else cout << ci << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}