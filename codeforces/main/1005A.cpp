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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<ll> len;
    for (ll i = 1; i < n; i++) {
        if (a[i] == 1) len.push_back(a[i - 1]); 
    }
    len.push_back(a.back());
    cout << len.size() << "\n";
    for (ll i = 0; i < len.size(); i++) cout << len[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}