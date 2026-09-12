#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

vector<ll> get_alpha(string s) {
    vector<ll> ans;
    set<char> unique(s.begin(), s.end());
    vector<ll> lt(unique.begin(), unique.end());

    ll start = 1;
    for (ll i = 0; i < lt.size() - 1; i++) start *= 10;
    for (ll i = start; i < start * 10; i++) {
        string mp = to_string(i);
        set<char> unique_mp(mp.begin(), mp.end());
        if (mp.size() != unique_mp.size()) continue;

        string curr = "";
        for (ll j = 0; j < s.size(); j++) {
            for (ll k = 0; k < lt.size(); k++) {
                if (s[j] == lt[k]) curr += mp[k];
            }
        }
        if (curr[0] == '0') continue;
        ans.push_back(stoll(curr));
    }

    return ans;
}

bool is_prime(ll n) {
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return (n > 1);
}

void solve() {
    string s;
    cin >> s;
    vector<ll> nums = get_alpha(s);
    for (ll k : nums) {
        if (is_prime(k)) {
            cout << k << "\n";
            return;
        }
    }
    cout << "-1\n";
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}