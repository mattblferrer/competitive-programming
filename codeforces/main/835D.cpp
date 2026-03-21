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
    ll n = s.size();
    vector<vector<ll>> palindrome(n, vector<ll>(n));
    for (ll i = 0; i < n; i++) palindrome[i][i] = true;
    for (ll d = 1; d <= n; d++) {
        for (ll i = 0; i < n; i++) {
            for (ll j = i + d; (j - i <= d) & (j < n); j++) {
                ll t = (j - i - 1) / 2;
                if ((j - i) > 1) palindrome[i][j] = (palindrome[i + 1][j - 1] > 0) & (s[i] == s[j]);
                else palindrome[i][j] = 2*(s[i] == s[j]);
                if ((palindrome[i][j]) && (palindrome[i][i + t] > 0) && (palindrome[i][i + t] == palindrome[j - t][j])) {
                    palindrome[i][j] = palindrome[i][i + t] + 1;
                }
            }
        }
    }
    vector<ll> ans(n + 1);
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            ans[palindrome[i][j]]++;
        }
    }
    for (ll i = n; i > 0; i--) {
        ans[i - 1] += ans[i];
    }
    for (ll i = 1; i <= n; i++) cout << ans[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}