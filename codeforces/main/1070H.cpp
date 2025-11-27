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
    map<string, set<ll>> num;
    map<string, string> name;
    for (ll i = 0; i < n; i++) {
        string f;
        cin >> f;
        for (ll j = 0; j < f.size(); j++) {
            for (ll k = 1; k < f.size() - j + 1; k++) {
                string sub = f.substr(j, k);
                num[sub].insert(i);
                name[sub] = f;
            }
        }
    }
    ll q;
    cin >> q;
    for (ll i = 0; i < q; i++) {
        string query;
        cin >> query;
        if (num[query].size() == 0) cout << "0 -\n";
        else cout << num[query].size() << " " << name[query] << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}