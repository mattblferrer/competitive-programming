#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;


int main() {
    ll n;
    cin >> n;
    vector<bool> truth;
    for (ll i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (s == "TRUTH") {
            truth.push_back(true);
        } else {
            truth.push_back(false);
        }
    }
    reverse(truth.begin(), truth.end());
    bool flip = false;
    for (auto x: truth) {
        if (flip) {
            x = x ^ 1;
        }
        flip = x ^ 1;
    }
    if (flip) {
        cout << "LIE";
    } else {
        cout << "TRUTH";
    }
    return 0;
}