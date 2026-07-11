#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
ll m, t;
constexpr ld PI = 3.14159265358979323846;
ld f(ll sides)
{
    ld side_length = t / (ld)sides - m;
    ld ans = (sides * side_length * side_length) / (4 * tanl(PI / sides));
    return ans;
}

ld ternary_search(ll l, ll r) {
    while (r - l > 2) {
        ll m1 = l + (r - l) / 3;
        ll m2 = r - (r - l) / 3;

        ld f1 = f(m1);
        ld f2 = f(m2);

        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }

    ll best = l;
    for (ll i = l; i <= r; i++) {
        if (f(i) > f(best)) best = i;
    }
    return f(best);
}

void solve() {
    int c;
    cin >> c;
    for (int i = 0; i < c; i++)
    {
        cin >> m >> t;
        if (t / m <= 3) cout << 0 << "\n";
        else cout << setprecision(20) << ternary_search(3, t / m) << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}