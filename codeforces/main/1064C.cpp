#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<char, int> cnt;
    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (char c = 'a'; c <= 'z'; c++) {
        for (int i = 0; i < cnt[c]; i++) cout << c;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}