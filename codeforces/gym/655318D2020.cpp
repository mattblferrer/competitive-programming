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
    ll a = 0, b = 0;
    string s = "";
    for (ll i = n; i > 0; i--) {
        if (a > b) {
            b += i;
            s += 'B';
        }
        else {
            a += i;
            s += 'A';
        }
    }
    reverse(s.begin(), s.end());
    cout << abs(a - b) << "\n" << s;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}