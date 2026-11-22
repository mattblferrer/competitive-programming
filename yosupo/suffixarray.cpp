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

// suffix array and LCP array
//   SuffixArray(s)   sa[i] = start of the i-th smallest suffix, rank = inverse of sa,
//                    lcp[i] = longest common prefix of suffixes sa[i] and sa[i + 1], O(n log n)
//   count(p)         number of occurrences of p in s, O(|p| log n)
struct SuffixArray {
    string s;
    int n;
    vector<int> sa, rank, lcp;

    SuffixArray(const string &str): s(str), n(str.size()) {
        string t = s + char(0);  // the sentinel sorts before every other character
        int m = n + 1, classes = 1;
        vector<int> p(m), c(m), np(m), nc(m), cnt(max(m, 256) + 1, 0);
        for (int i = 0; i < m; i++) cnt[(unsigned char)t[i]]++;
        for (int i = 1; i < 256; i++) cnt[i] += cnt[i - 1];
        for (int i = m - 1; i >= 0; i--) p[--cnt[(unsigned char)t[i]]] = i;
        c[p[0]] = 0;
        for (int i = 1; i < m; i++) {
            if (t[p[i]] != t[p[i - 1]]) classes++;
            c[p[i]] = classes - 1;
        }
        for (int h = 0; (1 << h) < m; h++) {
            for (int i = 0; i < m; i++) np[i] = (p[i] - (1 << h) + m) % m;
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < m; i++) cnt[c[np[i]]]++;
            for (int i = 1; i < classes; i++) cnt[i] += cnt[i - 1];
            for (int i = m - 1; i >= 0; i--) p[--cnt[c[np[i]]]] = np[i];
            nc[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < m; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % m]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % m]};
                if (cur != prev) classes++;
                nc[p[i]] = classes - 1;
            }
            c.swap(nc);
        }
        sa.assign(p.begin() + 1, p.end());  // drop the sentinel
        rank.assign(n, 0);
        for (int i = 0; i < n; i++) rank[sa[i]] = i;
        lcp.assign(max(n - 1, 0), 0);
        for (int i = 0, k = 0; i < n; i++) {
            if (rank[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[rank[i]] = k;
            if (k) k--;
        }
    }

    int count(const string &q) const {
        int m = q.size();
        int lo = partition_point(sa.begin(), sa.end(), [&](int i) { return s.compare(i, m, q) < 0; }) - sa.begin();
        int hi = partition_point(sa.begin(), sa.end(), [&](int i) { return s.compare(i, m, q) <= 0; }) - sa.begin();
        return hi - lo;
    }
};

void solve() {
    string s;
    cin >> s;
    SuffixArray sa(s);
    for (int i = 0; i < s.size(); i++) cout << sa.sa[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
