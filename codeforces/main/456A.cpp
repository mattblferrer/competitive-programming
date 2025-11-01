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
    vector<pll> lt(n);
    for (ll i = 0; i < n; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        lt[i] = {ai, bi};
    }
    sort(lt.begin(), lt.end());
    for (ll i = 0; i < n - 1; i++) {
        if (lt[i].second > lt[i + 1].second) {
            cout << "Happy Alex\n";
            return;
        }
    }
    cout << "Poor Alex\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}