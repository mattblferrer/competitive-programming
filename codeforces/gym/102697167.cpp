#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    string a, b;
    cin >> a >> b;
    ll a_val, b_val;
    if (a == "A") a_val = 11;
    else if (isalpha(a[0])) a_val = 10;
    else a_val = stoll(a);
    if (b == "A") b_val = 11;
    else if (isalpha(b[0])) b_val = 10;
    else b_val = stoll(b);
    ll need = 21 - a_val - b_val;
    if (need == 0) cout << "BLACKJACK";
    else if (need == 10) cout << "FACE CARD/10";
    else if ((need == 11) || (need == 1)) cout << "A";
    else if (need < 0) cout << need + 10;
    else cout << need;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}