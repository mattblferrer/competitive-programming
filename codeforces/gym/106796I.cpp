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
    int n;
    cin >> n;
    vector<ll> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    vector<int> rem(5);
    for (int i = 0; i < n; i++) {
        rem[p[i] % 5]++;
    }
    int ans = 0;
    for (int i = 0; i <= 2; i++) {
        ans += i * rem[i];
    }

    int max_34 = -999999999;
    for (int i = 0; i <= min(rem[3], rem[4]); i++) {
        int curr = 2 * i;
        curr += ((rem[3] - i) / 2) - 2 * ((rem[3] - i) % 2);
        curr += 2 * ((rem[4] - i) / 3) - ((rem[4] - i) % 3);
        max_34 = max(max_34, curr);
    }
    ans += max_34;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
