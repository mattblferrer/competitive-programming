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
    bool valid = true;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'R') {
            if (i == n - 1 || s[i + 1] == 'R') valid = false;
        }
    }
    if (valid) {
        cout << "YES\n";
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        string ns = s;  // new string
        char temp = ns[i];
        ns[i] = ns[i + 1];
        ns[i + 1] = temp;
        bool valid = true;
        for (int j = 0; j < n; j++) {
            if (ns[j] == 'R') {
                if (j == n - 1 || ns[j + 1] == 'R') valid = false;
            }
        }
        if (valid) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}