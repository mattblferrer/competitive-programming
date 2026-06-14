#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string n;
    cin >> n;
    if (n.size() < 3) cout << "byte";
    else if (n.size() == 3 && n <= "127") cout << "byte";
    else if (n.size() < 5) cout << "short";
    else if (n.size() <= 5 && n <= "32767") cout << "short";
    else if (n.size() < 10) cout << "int";
    else if (n.size() <= 10 && n <= "2147483647") cout << "int";
    else if (n.size() < 19) cout << "long";
    else if (n.size() <= 19 && n <= "9223372036854775807") cout << "long";
    else cout << "BigInteger";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}