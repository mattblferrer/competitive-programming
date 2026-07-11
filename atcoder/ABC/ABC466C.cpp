#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    ll ans = 0, left = 1, right = 2;

    while ((left != n + 1) && (right != n + 1)) {
        cout << "? " << left << " " << right << "\n" << flush;
        string resp;
        cin >> resp;
        if (resp == "Yes") {
            ans += (right - left);
            right++;
        }
        else left++;
        if (left == right) right++;
    }
    cout << "! " << ans << "\n" << flush;
}

int main() {
    solve();
    return 0;
}