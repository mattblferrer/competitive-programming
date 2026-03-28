#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

ld distance(ld x1, ld y1, ld x2, ld y2) {
    ld ax = abs(x1 - x2), ay = abs(y1 - y2);
    return powl(ax*ax + ay*ay, 0.5);
}

void solve() {
    ld ax, ay, bx, by, cx, cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    ld dist_ab = distance(ax, ay, bx, by);
    ld dist_bc = distance(bx, by, cx, cy);
    if (dist_ab != dist_bc) {
        cout << "No\n";
        return;
    }
    ld s1 = (by - ay)*(cx - bx);
    ld s2 = (cy - by)*(bx - ax);
    ld s3 = (cy - by)*(cx - bx);

    if ((s1 == s2) && (s2 == s3) && (s1 == s3)) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}