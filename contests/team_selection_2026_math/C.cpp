#include <bits/stdc++.h> 

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

ll mod(ll x, ll m) {
    if (m == 0) return 0;
    if (m < 0) m *= -1;
    return (x % m + m) % m;
}

ll extended_euclid(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll g = extended_euclid(b, a % b, x, y);
    ll z = x - a / b * y;
    x = y;
    y = z;
    return g;
}

pll chinese(ll b1, ll m1, ll b2, ll m2) {
    ll x, y;
    ll g = extended_euclid(m1, m2, x, y);
    if (b1 % g != b2 % g) return {-1, -1};
    ll M = abs(m1 / g * m2);
    return {mod(mod(x * b2 * m1 + y * b1 * m2, M * g) / g,M), M};
}

pll chinese_rem(vector<ll> b, vector<ll> m) {
    pll ans(0, 1);
    for (ll i = 0; i < b.size(); i++) {
        ans = chinese(b[i], m[i], ans.first, ans.second);
        if (ans.second == -1) break;
    }
    return ans;
}

int main() {
    ll n;
    string s;
    cin >> n >> s;

    vector<ll> mods, rem;
    string letters_avail = "";
    for (char c = 'A'; c < 'A' + n; c++) {
        letters_avail = letters_avail + c;
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < letters_avail.size(); j++) {
            if (letters_avail[j] == s[i]) {
                rem.push_back(j);
                letters_avail = letters_avail.substr(0, j) + letters_avail.substr(j + 1, letters_avail.size());
                break;
            }
        }
    }
    for (ll i = n; i >= 1; i--) mods.push_back(i);

    pll ans = chinese_rem(rem, mods);
    if (ans.second == -1) {
        cout << "NO\n";
    }
    else {
        cout << "YES\n";
        cout << ans.first;
    }

    return 0;
}