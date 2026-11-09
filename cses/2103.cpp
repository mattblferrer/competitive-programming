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

// suffix automaton over lowercase letters; each state is a set of substrings with the same end positions
// SuffixAutomaton(s) is ready to use; after calling extend yourself, call compute_counts before occurrences
//   SuffixAutomaton(s)    build from s, O(n * 26)
//   extend(c)             append c to the string, O(26) amortized
//   compute_counts()      fill cnt[state] = number of end positions of that state, O(states)
//   contains(p)           true if p is a substring, O(|p|)
//   occurrences(p)        number of occurrences of p in the string, O(|p|)
//   distinct()            number of distinct non-empty substrings, O(states)
//   lcs(t)                length of the longest common substring with t, O(|t|)
struct SuffixAutomaton {
    struct State {
        int len, link;
        bool clone;
        array<int, 26> next;
    };
    vector<State> st;
    vector<ll> cnt;
    int last = 0;

    SuffixAutomaton(const string &s = "") {
        State root;
        root.len = 0;
        root.link = -1;
        root.clone = false;
        root.next.fill(-1);
        st.push_back(root);
        for (char c : s) extend(c);
        compute_counts();
    }

    void extend(char ch) {
        int c = ch - 'a', cur = st.size();
        State node;
        node.len = st[last].len + 1;
        node.link = 0;
        node.clone = false;
        node.next.fill(-1);
        st.push_back(node);
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p != -1) {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            }
            else {
                int cl = st.size();
                State copy = st[q];
                copy.len = st[p].len + 1;
                copy.clone = true;
                st.push_back(copy);
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = cl;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = cl;
            }
        }
        last = cur;
    }

    void compute_counts() {
        int m = st.size();
        cnt.assign(m, 0);
        vector<int> order(m), bucket(st[last].len + 2, 0);
        for (int i = 0; i < m; i++) bucket[st[i].len]++;
        for (int i = 1; i < (int)bucket.size(); i++) bucket[i] += bucket[i - 1];
        for (int i = m - 1; i >= 0; i--) order[--bucket[st[i].len]] = i;
        for (int i = 1; i < m; i++) if (!st[i].clone) cnt[i] = 1;
        for (int i = m - 1; i > 0; i--) cnt[st[order[i]].link] += cnt[order[i]];
    }

    int find_state(const string &p) const {
        int v = 0;
        for (char ch : p) {
            v = st[v].next[ch - 'a'];
            if (v == -1) return -1;
        }
        return v;
    }

    bool contains(const string &p) const { return find_state(p) != -1; }

    ll occurrences(const string &p) const {
        int v = find_state(p);
        return v == -1 ? 0 : cnt[v];
    }

    ll distinct() const {
        ll res = 0;
        for (int i = 1; i < (int)st.size(); i++) res += st[i].len - st[st[i].link].len;
        return res;
    }

    int lcs(const string &t) const {
        int v = 0, len = 0, best = 0;
        for (char ch : t) {
            int c = ch - 'a';
            while (v != 0 && st[v].next[c] == -1) {
                v = st[v].link;
                len = st[v].len;
            }
            if (st[v].next[c] != -1) {
                v = st[v].next[c];
                len++;
            }
            best = max(best, len);
        }
        return best;
    }
};

void solve() {
    string s;
    cin >> s;
    ll k;
    cin >> k;
    SuffixAutomaton sfa(s);
    vector<string> p(k);
    for (ll i = 0; i < k; i++) {
        cin >> p[i];
        cout << sfa.occurrences(p[i]) << "\n";
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
