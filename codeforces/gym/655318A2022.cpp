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
    bool a = true, b = true, c = true;
    string as = "Alice", bs = "Bob", cs = "Cindy";
    if (s.size() == 5) {
        b = false;
        for (ll i = 0; i < 5; i++) {
            if ((s[i] != '.') && (s[i] != as[i])) a = false;
            if ((s[i] != '.') && (s[i] != cs[i])) c = false;
        }
    }
    else if (s.size() == 3) {
        a = c = false;
        for (ll i = 0; i < 3; i++) {
            if ((s[i] != '.') && (s[i] != bs[i])) b = false;
        }
    }
    else {
        cout << "SOMETHING'S WRONG";
        return;
    }
    if (a + b + c > 1) cout << "CAN'T TELL";
    else if (a + b + c == 0) cout << "SOMETHING'S WRONG";
    else if (a) cout << "Alice";
    else if (b) cout << "Bob";
    else if (c) cout << "Cindy";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}