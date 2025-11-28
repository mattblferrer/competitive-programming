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
    map<string, vector<ll>> spec;
    multiset<pair<ll, string>, greater<pair<ll, string>>> ms;
    for (ll i = 0; i < n; i++) {
        string view;
        ll ai;
        cin >> view >> ai;
        spec[view].push_back(ai);
        ms.insert({ai, view});
    }
    ll ans = 0;
    for (auto pair: spec) {
        sort(spec[pair.first].begin(), spec[pair.first].end(), greater<ll>());
    }
    // always optimal for 11
    for (ll i = 0; i < spec["11"].size(); i++) {  
        ans += spec["11"][i];
        ms.extract({spec["11"][i], "11"});
    }
    // match 01 with 10
    for (ll i = 0; i < min(spec["01"].size(), spec["10"].size()); i++) {  
        ans += spec["01"][i] + spec["10"][i];
        ms.extract({spec["01"][i], "01"});
        ms.extract({spec["10"][i], "10"});
    }
    // get remaining possible candidates
    ll ext = 0;
    for (auto pair: ms) {
        if (ext == spec["11"].size()) break;
        ext++;
        ans += pair.first;
    }
    cout << ans;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}