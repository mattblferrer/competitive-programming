#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

vector<vector<ll>> ans;
vector<ll> curr;

void get_sequences(vector<ll> &curr, ll n, ll m) {
    if (curr.size() == n) {
        ans.push_back(curr);
        return;
    }
    ll start = 1;
    if (!curr.empty()) start = curr.back() + 10;
    ll limit = m - (n - curr.size() - 1) * 10;

    for (ll i = start; i <= limit; i++) {
        curr.push_back(i);
        get_sequences(curr, n, m);
        curr.pop_back();
    }
}

void solve() {
    ll n, m;
    cin >> n >> m;
    get_sequences(curr, n, m);
    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) {
        for (ll j = 0; j < n; j++) cout << ans[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}