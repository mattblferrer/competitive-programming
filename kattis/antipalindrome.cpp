#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

bool is_palindrome(string s) {
    for (int i = 0; i <= s.size() / 2; i++) {
        if (s[i] != s[s.size() - i - 1]) return false;
    }
    return true;
}

void solve() {
    string in;
    getline(cin, in);
    string s = "";
    for (int i = 0; i < in.size(); i++) {
        if (isalpha(in[i])) {
            if (isupper(in[i])) s += (in[i] + 32);
            else s += in[i];
        }
    }   
    int n = s.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 2; j <= n - i; j++) {
            if (is_palindrome(s.substr(i, j))) {
                cout << "Palindrome";
                return;
            }
        }
    }
    cout << "Anti-palindrome";
    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}