#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    vector<ll> a(5);
    for (ll i = 0; i < 5; i++) cin >> a[i];
    for (ll i = 0; i < 4; i++) {
        ll temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
        bool sorted = true;
        for (ll j = 0; j < 4; j++) {
            if (a[j] != a[j + 1] - 1) sorted = false;
        }
        if (sorted) {
            cout << "Yes\n";
            return;
        }
        temp = a[i];
        a[i] = a[i + 1];
        a[i + 1] = temp;
    }
    cout << "No\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}