#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll a, b;
    cin >> a >> b;
    for (ll i = a; i < b; i++) {
        string out = "";
        if (i % 3 == 0) out += "Fizz";
        if (i % 5 == 0) out += "Buzz";
        if (out != "") cout << out;
        else cout << i;
        cout << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}