#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ld t1, t2, t3, r1, r2, r3;
    cin >> t1 >> t2 >> t3 >> r1 >> r2 >> r3;
    ld l1 = log(r1), l2 = log(r2), l3 = log(r3);
    ld y1 = 1/t1, y2 = 1/t2, y3 = 1/t3;
    ld k2 = (y2 - y1)/(l2 - l1);
    ld k3 = (y3 - y1)/(l3 - l1);
    ld c = ((k3 - k2)/(l3 - l2)) * (1/(l1 + l2 + l3));
    ld b = k2 - c*(l1*l1 + l1*l2 + l2*l2);
    ld a = y1 - l1*(b + l1*l1*c);
    cout << a;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}