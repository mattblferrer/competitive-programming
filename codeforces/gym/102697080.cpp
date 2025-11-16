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
    getline(cin, s);
    for (char c: s) {
        if (c == 'a') cout << '4';
        else if (c == 'b') cout << '8';
        else if (c == 'e') cout << '3';
        else if (c == 'i') cout << '1';
        else if (c == 'l') cout << '1';
        else if (c == 'o') cout << '0';
        else if (c == 's') cout << '5';
        else if (c == 't') cout << '7';
        else if (c == 'z') cout << '2';
        else cout << c;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}