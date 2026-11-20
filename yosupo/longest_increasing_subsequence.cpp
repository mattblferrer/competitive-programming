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

// indices of a longest strictly increasing subsequence of a, O(n log n)
vector<int> lis(const vector<ll> &a) {
    int n = a.size();
    vector<int> seq, prev(n, -1), ans;  // seq[k] = index of the smallest tail of an increasing subsequence of length k + 1
    for (int i = 0; i < n; i++) {
        int k = partition_point(seq.begin(), seq.end(), [&](int j) { return a[j] < a[i]; }) - seq.begin();
        if (k) prev[i] = seq[k - 1];
        if (k == (int)seq.size()) seq.push_back(i);
        else seq[k] = i;
    }
    for (int at = seq.empty() ? -1 : seq.back(); at != -1; at = prev[at]) ans.push_back(at);
    reverse(ans.begin(), ans.end());
    return ans;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<int> ans = lis(a);
    cout << ans.size() << "\n";
    for (ll i = 0; i < ans.size(); i++) cout << ans[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
