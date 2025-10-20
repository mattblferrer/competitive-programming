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
    map<char, int> cnt;
    for (char c: s) cnt[c]++;
    if (cnt['4'] == 0 && cnt['7'] == 0) cout << -1;
    else if (cnt['4'] >= cnt['7']) cout << 4;
    else cout << 7;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}