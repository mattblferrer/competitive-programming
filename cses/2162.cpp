#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
    ll n;
    cin >> n;
    indexed_set<ll> a;
    for (ll i = 1; i <= n; i++) a.insert(i);
    for (ll i = 1; a.size() > 0; i++) {
        if (i >= a.size()) i = i % a.size();
        ll curr = *a.find_by_order(i);
        cout << curr << " ";
        a.erase(curr);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}