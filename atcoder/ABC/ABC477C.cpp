#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll q;
    cin >> q;
    string s, t;
    cin >> s >> t;

    vector<ll> matches;
    for (ll i = 0; i < s.size(); i++) {
        string curr = "";
        for (ll j = i; j < i + t.size(); j++) {
            if (j >= s.size()) break;
            curr += s[j];
        }
        if (curr == t) {
            matches.push_back(i);
        }
    }

    for (ll qi = 0; qi < q; qi++) {
        ll l, r;
        cin >> l >> r;
        l--; r--;

        auto it = lower_bound(matches.begin(), matches.end(), l);
        if (it == matches.end()) {
            cout << "No\n";
        }
        else if ((*(it)) + t.size() - 1 <= r) {
            cout << "Yes\n";
        }
        else cout << "No\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}