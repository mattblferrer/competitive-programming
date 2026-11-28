#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, q;
    cin >> n >> q;
    map<pair<string, ll>, ll> prod_number;
    map<ll, vector<string>> products;
    for (ll i = 0; i < n; i++) {
        string si;
        ll vi;
        cin >> si >> vi;
        if (prod_number.count({si, vi}) == 0) prod_number[{si, vi}] = i + 1;
        products[vi].push_back(si);
    }
    products[-INT_MAX] = {};
    products[INT_MAX] = {};
    for (ll i = 0; i < q; i++) {
        ll xj;
        cin >> xj;
        if (products.count(xj)) {
            for (string si : products[xj]) cout << si << " ";
            cout << "\n";
            continue;
        }
        ll low = prev(products.lower_bound(xj))->first;
        ll high = products.upper_bound(xj)->first;
        if (products[low].size() == 0) cout << products[high][0] << "\n";
        else if (products[high].size() == 0) cout << products[low][0] << "\n";
        else if ((xj - low) < (high - xj)) cout << products[low][0] << "\n";
        else if ((xj - low) > (high - xj)) cout << products[high][0] << "\n";
        else if (prod_number[{products[high][0], high}] < prod_number[{products[low][0], low}]) {
            cout << products[high][0] << "\n";
        }
        else cout << products[low][0] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}