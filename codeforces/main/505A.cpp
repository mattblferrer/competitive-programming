#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_palindrome(string s) {
    ll n = s.size();
    for (ll i = 0; i < n; i++) {
        if (s[i] != s[n - i - 1]) return false;
    }
    return true;
}

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    for (ll i = 0; i <= n; i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            string s_new = s.substr(0, i) + c + s.substr(i, n - i);
            if (is_palindrome(s_new)) {
                cout << s_new << "\n";
                return;
            }
        }
    }
    cout << "NA\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}