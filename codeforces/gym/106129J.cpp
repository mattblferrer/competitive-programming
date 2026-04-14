#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string choice, s;
    ll n;
    cin >> choice >> n >> s;
    if (choice == "Encode") {
        ll l = -1;
        for (ll i = 0; i < n; i++) {
            if (s[i] == '1') {
                l = i;
                break;
            }
        }
        if (l == -1) {
            cout << s;
            return;
        }
        for (ll i = 0; i <= l; i++) cout << '2';
        for (ll i = l + 1; i < n; i++) cout << s[i]; 
    }
    else if (choice == "Decode") {
        ll c2 = 0;
        for (ll i = 0; i < n; i++) if (s[i] == '2') c2++;
        if (c2 == 0) {
            for (ll i = 0; i < n; i++) cout << '0';
            return;
        }
        if (c2 == n) { 
            for (ll i = 0; i < n - 1; i++) cout << '0'; 
            cout << '1';
            return; 
        }
        string ss = s + s;
        ll start = -1;
        for (ll i = 1; i < 2*n; i++) {
            if ((ss[i] != '2') && (ss[i - 1] == '2')) {
                start = i % n;
                break;
            }
        }
        for (ll i = 0; i < c2 - 1; i++) cout << '0';
        cout << '1';
        for (ll i = 0; i < n - c2; i++) cout << s[(start + i) % n];
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    cout << "\n";
    return 0;
}