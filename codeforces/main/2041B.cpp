#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll w, b;
    cin >> w >> b;
    ll left = -1, right = w + b + 1;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        if ((w + b) < mid*(mid + 1)/2) right = mid; 
        else left = mid; 
    }
    cout << left << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}