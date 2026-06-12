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
    string s, t;
    cin >> s >> t;

    // check if two strings have equal freq
    string s_sort = s, t_sort = t;
    sort(s_sort.begin(), s_sort.end());
    sort(t_sort.begin(), t_sort.end());
    if (s_sort != t_sort) {
        cout << -1;
        return;
    }
    vector<ll> ans, ans_t;
    for (ll i = 0; i < n - 1; i++) {
        for (ll j = 0; j < n - 1; j++) {
            if (s[j] > s[j + 1]) {
                swap(s[j], s[j + 1]);
                ans.push_back(j + 1);
            }
        }
    }
    for (ll i = 0; i < n - 1; i++) {
        for (ll j = 0; j < n - 1; j++) {
            if (t[j] > t[j + 1]) {
                swap(t[j], t[j + 1]);
                ans_t.push_back(j + 1);
            }
        }
    }
    reverse(ans_t.begin(), ans_t.end());
    ans.insert(ans.end(), ans_t.begin(), ans_t.end());
    cout << ans.size() << "\n";
    for (ll x : ans) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}