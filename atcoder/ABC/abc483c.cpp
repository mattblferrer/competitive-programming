// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 1'000'000'007;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

void solve() {
    ll n, m;
    cin >> n >> m;
    vector<pll> votes(m + 1);

    for (ll i = 1; i <= m; i++) {
        ll ai, bi;
        cin >> ai >> bi;
        votes[i] = {ai, bi};
    }

    vector<ll> cnt(n + 1);
    vector<vector<ll>> se(n + 1);
    for (ll i = 1; i <= m; i++) {
        cnt[votes[i].first]++;
        se[votes[i].first].push_back(votes[i].second);
    }

    set<pll> cnt_set;
    for (ll i = 1; i <= n; i++) cnt_set.insert({-cnt[i], i});

    for (ll i = 1; i <= n; i++) {
        cnt_set.erase({-cnt[i], i});
        for (ll j = 0; j < se[i].size(); j++) {
            cnt_set.erase({-cnt[se[i][j]], se[i][j]});
            cnt[se[i][j]]++;
            cnt_set.insert({-cnt[se[i][j]], se[i][j]});
        }
        cout << cnt_set.begin()->second << "\n";
        for (ll j = 0; j < se[i].size(); j++) {

            cnt_set.erase({-cnt[se[i][j]], se[i][j]});
            cnt[se[i][j]]--;
            cnt_set.insert({-cnt[se[i][j]], se[i][j]});
        }
        cnt_set.insert({-cnt[i], i});
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
