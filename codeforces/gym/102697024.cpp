#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s1, s2;
    cin >> s1 >> s2;
    ll b1, b2, tp1, tp2, ft1, ft2;
    cin >> b1 >> b2 >> tp1 >> tp2 >> ft1 >> ft2;
    ll score1 = (b1 - tp1)*2 + tp1*3 + ft1;
    ll score2 = (b2 - tp2)*2 + tp2*3 + ft2;
    if (score1 < score2) cout << s2;
    else cout << s1;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}