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

// palindromic tree (eertree) over lowercase letters; each node is a distinct palindromic substring
//   add(c)            append c to the string, O(1) amortized
//   unique()          number of distinct palindromic substrings, O(1)
//   occurrences()     occurrences of each node's palindrome (index = node id), O(nodes)
//   total()           number of palindromic substrings, counted with multiplicity, O(nodes)
//   longest()         {start, length} of a longest palindromic substring, O(1)
struct Eertree {
    struct Node {
        int len, link;
        ll end_count;  // number of positions where this is the longest palindromic suffix
        array<int, 26> next;
    };
    vector<Node> t;  // node 0 has length -1, node 1 has length 0
    string s;
    int last = 1, best_end = -1, best_len = 0;

    Eertree() {
        Node a;
        a.len = -1;
        a.link = 0;
        a.end_count = 0;
        a.next.fill(0);
        t.push_back(a);
        a.len = 0;
        t.push_back(a);
    }

    int get_link(int v, int i) const {
        while (i - t[v].len - 1 < 0 || s[i - t[v].len - 1] != s[i]) v = t[v].link;
        return v;
    }

    void add(char ch) {
        s.push_back(ch);
        int i = s.size() - 1, c = ch - 'a';
        int cur = get_link(last, i);
        if (!t[cur].next[c]) {
            Node a;
            a.len = t[cur].len + 2;
            a.link = a.len == 1 ? 1 : t[get_link(t[cur].link, i)].next[c];
            a.end_count = 0;
            a.next.fill(0);
            t.push_back(a);
            t[cur].next[c] = t.size() - 1;
        }
        last = t[cur].next[c];
        t[last].end_count++;
        if (t[last].len > best_len) {
            best_len = t[last].len;
            best_end = i;
        }
    }

    int unique() const { return t.size() - 2; }

    vector<ll> occurrences() const {
        vector<ll> cnt(t.size());
        for (int i = 0; i < (int)t.size(); i++) cnt[i] = t[i].end_count;
        for (int i = (int)t.size() - 1; i >= 2; i--) cnt[t[i].link] += cnt[i];  // a link always has a smaller index
        return cnt;
    }

    ll total() const {
        vector<ll> cnt = occurrences();
        return accumulate(cnt.begin() + 2, cnt.end(), 0LL);
    }

    pair<int, int> longest() const { return {best_end - best_len + 1, best_len}; }
};

void solve() {
    string s;
    cin >> s;
    Eertree et;
    for (int i = 0; i < s.size(); i++) et.add(s[i]);
    auto [start, len] = et.longest();
    cout << s.substr(start, len) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
