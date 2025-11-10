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
        if ((c != 'a') && (c != 'b')) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    
    solve();
    return 0;
}