#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n, k;
    cin >> n >> k;
    int d = n * n - k;
    if (d == 0) {
        cout << "YES\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) cout << "D";
            cout << "\n";
        }
        return;
    }
    if (d >= 2) {
        cout << "YES\n";
        d -= 2;
        for (int i = 0; i < n; i++) {
            if (i == 0) {
                cout << "RL";
                for (int j = 2; j < n; j++) {
                    if (d) {
                        cout << "L";
                        d--;
                    }
                    else cout << "D";
                }
            }
            else {
                for (int j = 0; j < n; j++) {
                    if (d) {
                        cout << "U";
                        d--;
                    }
                    else cout << "D";
                }
            }
            cout << "\n";
        }
        return;
    }
    cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}