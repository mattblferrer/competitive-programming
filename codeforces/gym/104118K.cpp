#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    string s;
    vector<bool> letters(26);
    for (int i = 0; i < 3; i++) {
        cin >> s;
        for (char c: s) {
            if (c != '*') letters[c - 'A'] = 1;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> s;
        bool p = true;  // if possible
        vector<bool> sl(26);
        for (char c: s) sl[c - 'A'] = 1;
        for (int j = 0; j < 26; j++) {
            if (letters[j] == sl[j]) p = false;
        }
        if (p) cout << "POSSIBLE\n";
        else cout << "IMPOSSIBLE\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}