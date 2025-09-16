#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    ll q, c, k, v;
    cin >> q;
    map<ll, ll> a;
    for (ll i = 0; i < q; i++) {
        cin >> c;
        if (c == 0) {
            cin >> k >> v;
            a[k] = v;
        }
        else if (c == 1) {
            cin >> k;
            cout << a[k] << "\n";
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}