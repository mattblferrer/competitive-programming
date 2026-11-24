// github.com/mattblferrer/competitive-programming

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
const ld PI = acosl(-1);
const ll INF = 2e18;
const ll MOD = 998'244'353;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#endif

// multiset of integers in [0, 2^BITS)
//   insert(x)    add one copy of x, O(BITS)
//   erase(x)     remove one copy of x; x must be present, O(BITS)
//   nth(k)       k-th smallest element (0-indexed); requires k < size, O(BITS)
//   rank(x)      number of elements < x, for x < 2^BITS, O(BITS); with nth: successor = nth(rank(x)), predecessor = nth(rank(x + 1) - 1)
//   cnt[0][x]    number of copies of x
template <int BITS = 20>
struct MisofTree {
    vector<vector<int>> cnt;

    MisofTree(): cnt(BITS) {
        for (int i = 0; i < BITS; i++) cnt[i].assign(1 << (BITS - i), 0);
    }

    void insert(int x) {
        for (int i = 0; i < BITS; i++, x >>= 1) cnt[i][x]++;
    }

    void erase(int x) {
        for (int i = 0; i < BITS; i++, x >>= 1) cnt[i][x]--;
    }

    int nth(int k) const {
        int res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            res <<= 1;
            if (cnt[i][res] <= k) {
                k -= cnt[i][res];
                res |= 1;
            }
        }
        return res;
    }

    int rank(int x) const {
        int res = 0;
        for (int i = 0; i < BITS; i++, x >>= 1) if (x & 1) res += cnt[i][x - 1];  // the left sibling is all smaller
        return res;
    }
};

void solve() {
    ll n, q;
    string t;
    cin >> n >> q >> t;
    MisofTree<24> s;  // n <= 10^7 < 2^24
    ll sz = 0;
    for (ll i = 0; i < n; i++) {
        if (t[i] == '1') {
            s.insert(i);
            sz++;
        }
    }
    for (ll i = 0; i < q; i++) {
        ll c, k;
        cin >> c >> k;
        if (c == 0) {
            if (!s.cnt[0][k]) {
                s.insert(k);
                sz++;
            }
        }
        else if (c == 1) {
            if (s.cnt[0][k]) {
                s.erase(k);
                sz--;
            }
        }
        else if (c == 2) {
            cout << s.cnt[0][k] << "\n";
        }
        else if (c == 3) {
            ll r = s.rank(k);
            cout << (r < sz ? s.nth(r) : -1) << "\n";
        }
        else if (c == 4) {
            ll r = s.rank(k + 1);
            cout << (r > 0 ? s.nth(r - 1) : -1) << "\n";
        }
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
