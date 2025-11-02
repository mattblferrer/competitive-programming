#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll q;
    cin >> q;
    set<pll> mc, pc;
    ll in = 1;
    for (ll i = 0; i < q; i++) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll m;
            cin >> m;
            mc.insert({in, -m});
            pc.insert({-m, in});
            in++;
        }
        else if (op == 2) {
            ll f = mc.begin()->first, s = mc.begin()->second;
            cout << f << " ";
            mc.erase({f, s});
            pc.erase({s, f});
        }
        else if (op == 3) {
            ll f = pc.begin()->first, s = pc.begin()->second;
            cout << s << " ";
            mc.erase({s, f});
            pc.erase({f, s});
        }
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}