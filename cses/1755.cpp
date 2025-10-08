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
    vector<int> cnt(26);
    for (int i = 0; i < s.size(); i++) {
        cnt[s[i] - 'A']++;
    }
    int odd = 0;
    char oddc = '-';
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2 == 1) {
            odd++;
            oddc = (char)(i + 'A');
        }
    }
    if (odd >= 2) {
        cout << "NO SOLUTION";
        return;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (cnt[c - 'A'] % 2 == 1) continue;
        for (int j = 0; j < cnt[c - 'A'] / 2; j++) cout << c; 
    }
    if (oddc != '-') {
        for (int i = 0; i < cnt[oddc - 'A']; i++) cout << oddc; 
    }
    for (char c = 'Z'; c >= 'A'; c--) {
        if (cnt[c - 'A'] % 2 == 1) continue;
        for (int j = 0; j < cnt[c - 'A'] / 2; j++) cout << c; 
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}