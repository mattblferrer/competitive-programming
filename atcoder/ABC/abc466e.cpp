#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<pll> cards(n + 1);
    for (ll i = 1; i <= n; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        cards[i] = {ai, bi};
    }
    for (ll it = 0; it < k; it++) {
        ll temp = 0, left = 0, right = 0, max_flip = 0, curr = 0;
        vector<ll> diff(n + 1);
        for (ll i = 1; i <= n; i++) diff[i] = cards[i].second - cards[i].first;

        for (ll i = 1; i <= n; i++) {
            curr += diff[i];
            if (curr > max_flip) {
                max_flip = curr;
                left = temp;
                right = i;
            }
            if (curr < 0) {
                curr = 0;
                temp = i + 1;
            }
        }
        for (ll i = left; i <= right; i++) {
            swap(cards[i].first, cards[i].second);
        }
    }
    ll ans = 0;
    for (ll i = 1; i <= n; i++) ans += cards[i].first;
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}