#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, d;
    cin >> n >> d;
    string s;
    vector<ll> a(n), pos, neg;
    map<ll, ll> posc, negc;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    cin >> s;
    for (ll i = 0; i < n; i++) {
        if (s[i] == '+') {
            pos.push_back(a[i]);
            posc[a[i]]++;
        }
        else {
            neg.push_back(a[i]);
            negc[a[i]]++;
        }
    }
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll low, high;
        if (s[i] == '+') {
            low = distance(neg.begin(), lower_bound(neg.begin(), neg.end(), a[i]));
            high = distance(neg.begin(), lower_bound(neg.begin(), neg.end(), a[i] + d + 1));
            ans += high - low - negc[a[i]];
        }
        else {
            low = distance(pos.begin(), lower_bound(pos.begin(), pos.end(), a[i]));
            high = distance(pos.begin(), lower_bound(pos.begin(), pos.end(), a[i] + d + 1));
            ans += high - low - posc[a[i]];
        }
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