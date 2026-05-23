#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<int> ones = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4};
    vector<int> teens = {3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
    vector<int> tens = {0, 0, 6, 6, 5, 5, 5, 7, 6, 6};
    int ans = 0;
    for (int i = 1; i <= 1000; i++) {
        int k = i;
        if (k >= 1000) {
            ans += ones[k / 1000] + 8;  // thousand = 8 letters
            k = k % 1000;
        }
        if (k >= 100) {
            ans += ones[k / 100] + 7;  // hundred = 7 letters
            k = k % 100;
            if (k > 0) ans += 3;  // and = 3 letters
        }
        if (k >= 20) ans += tens[k / 10] + ones[k % 10];
        else if (k >= 10) ans += teens[k - 10];
        else ans += ones[k];
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}