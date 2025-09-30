#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

ll r, n;
vector<ll> d;

ll add(ll a, ll b) {
    if (b > 0) {
        a = (min(r, a + b));
    } else {
        a = max((ll)0, a + b);
    }
    return a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cin >> r >> n;
    for (ll i = 0; i < n; i++) {
        ll temp; cin >> temp;
        d.push_back(temp);
    }
    ll a = 0, b = r;
    for (ll i = 0; i < n; i++) {
        a = add(a, d[i]);
        b = add(b, d[i]);
    }
    if (a == b) {
        cout << a;
    } else {
        cout << "uncertain";
    }
    return 0;
}