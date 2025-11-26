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
    map<char, ll> cnt;
    for (ll i = 0; i < s.size(); i++) {
        cnt[s[i]]++;
    }
    char max_char = 'a';
    for (const auto pair: cnt) {
        if (pair.first > max_char) max_char = pair.first;
    }
    for (ll i = 0; i < cnt[max_char]; i++) {
        cout << max_char;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}