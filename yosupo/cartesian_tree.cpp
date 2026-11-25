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

// parent of each index in the Cartesian tree of a: the minimum is the root, and each side of it recursively
// (equal values: the leftmost is the ancestor); -1 for the root, O(n)
vector<int> cartesian_tree(const vector<ll> &a) {
    int n = a.size();
    vector<int> par(n, -1), st;
    for (int i = 0; i < n; i++) {
        int last = -1;
        while (!st.empty() && a[st.back()] > a[i]) {
            last = st.back();
            st.pop_back();
        }
        if (last != -1) par[last] = i;
        if (!st.empty()) par[i] = st.back();
        st.push_back(i);
    }
    return par;
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    vector<int> par = cartesian_tree(a);
    for (ll i = 0; i < n; i++) cout << (par[i] == -1 ? i : par[i]) << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
