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
    vector<ll> a(n);
    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    vector<pll> pairs;
    for (const auto& pair: cnt) pairs.push_back(pair);
    reverse(pairs.begin(), pairs.end());
    ll oc = 0, used = 0, sum = 0;
    vector<ll> extra;
    for (ll i = 0; i < pairs.size(); i++) {
        ll side = pairs[i].first, k = pairs[i].second;
        sum += side * k;
        used += k;
        if (k % 2 == 1) {
            if (oc >= 2) {
                sum -= side;
                used--;
                extra.push_back(side);
            }
            oc++;
        }
    }
    for (ll i = 0; i < pairs.size(); i++) {
        if ((pairs[i].first >= (sum - pairs[i].first)) && (pairs[i].second == 1)) {  // too long side
            sum -= pairs[i].first;
            if (i < extra.size()) sum += extra[i];
            else used--;
        }
        else break;
    }
    if (used < 3) {  // too few sides
        cout << "0\n";
        return;
    }
    cout << sum << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}