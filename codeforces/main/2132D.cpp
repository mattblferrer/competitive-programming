#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

map<ll, ll> dp;

ll sum_of_digits(ll n) {
    if (dp.count(n)) return dp[n];
    if (n < 10) {
        dp[n] = n*(n + 1)/2;
        return dp[n];
    }
    ll tens = n / 10, ones = n % 10;
    ll sum_tens = 0;
    string tens_str = to_string(tens);
    for (ll i = 0; i < tens_str.size(); i++) sum_tens += tens_str[i] - '0';
    ll ans = 45*tens + 10*sum_of_digits(tens - 1) + ((ones*(ones + 1))/2) + ((ones + 1)*sum_tens);
    dp[n] = ans;
    return ans;
}

void solve() {
    ll k;
    cin >> k;
    vector<ll> bp{0};
    ll curr = 1;
    while (bp.back() < powl(10, 18)) {
        bp.push_back(bp.back() + curr*9*powl(10, curr - 1));
        curr++;
    }
    ll maxd = 0;
    for (ll i = 0; i < bp.size(); i++) {
        if (bp[i] > k) {
            maxd = i - 1;
            break;
        }
    }
    ll stop = powl(10, maxd) + ((k - bp[maxd]) / (maxd + 1)) - 1;

    ll extra = (k - bp[maxd]) % (maxd + 1);
    ll ans = sum_of_digits(stop);
    string last = to_string(stop + 1);
    for (ll i = 0; i < extra; i++) ans += (last[i] - '0');
    cout << ans << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}