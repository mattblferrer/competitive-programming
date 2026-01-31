#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, m, k;
    string a, b;
    cin >> n >> m >> k >> a >> b;
    string c = "";
    sort(a.begin(), a.end(), greater<char>());
    sort(b.begin(), b.end(), greater<char>());
    ll ac = 0, bc = 0;
    for (ll i = 0; i < n + m; i++) {
        if ((a.size() == 0) || (b.size() == 0)) break;
        if (a.back() > b.back()) {
            if (bc < k) {
                c.push_back(b.back());
                b.pop_back();
                bc++;
                ac = 0;
            }
            else {
                c.push_back(a.back());
                a.pop_back();
                ac++;
                bc = 0;
            }
        }
        else {
            if (ac < k) {
                c.push_back(a.back());
                a.pop_back();
                ac++;
                bc = 0;
            }
            else {
                c.push_back(b.back());
                b.pop_back();
                bc++;
                ac = 0;
            }
        }
    }
    cout << c << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}