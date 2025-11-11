#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string s;
    cin >> s;
    for (char c: s) {
        if (c == 'h') {
            for (ll i = 0; i < 5; i++) cout << c;
        }
        else if (c == 'c') {
            for (ll i = 0; i < 2; i++) cout << c;
        }
        else if (c == 'z') {
            for (ll i = 0; i < 12; i++) cout << c;
        }
        else cout << c;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}