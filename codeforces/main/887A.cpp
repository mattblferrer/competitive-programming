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
    int n = s.size();
    int first = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            first = i;
            break;
        }
    }
    if (first == -1) {
        cout << "no\n";
        return;
    }
    int cnt = 0;
    for (int i = first; i < n; i++) {
        if (s[i] == '0') cnt++;
    }
    if (cnt >= 6) cout << "yes\n";
    else cout << "no\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}