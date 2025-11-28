#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n);
    ll sum = 0;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    if (sum % k != 0) {
        cout << "No\n";
        return;
    }
    ll curr = 0, sz = 0;
    vector<ll> idx;
    for (ll i = 0; i < n; i++) {
        curr += a[i];
        sz++;
        if (curr == sum / k) {
            idx.push_back(sz);
            curr = 0;
            sz = 0;
        }
        else if (curr > sum / k) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    for (ll i = 0; i < idx.size(); i++) cout << idx[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}