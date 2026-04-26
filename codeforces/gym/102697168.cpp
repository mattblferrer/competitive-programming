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
    vector<ll> row = {1};
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < row.size(); j++) cout << row[j] << " ";
        cout << "\n";
        vector<ll> new_row = {1};
        for (ll j = 0; j < i; j++) new_row.push_back(row[j] + row[j + 1]);
        new_row.push_back(1);
        row = new_row;
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}