#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// prefix function, O(n): pi[i] = length of the longest proper prefix of s[0..i] that is also a suffix
vector<int> prefix_function(const string &s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

// start indices of all occurrences of f in s, O(|s| + |f|)
vector<int> kmp(const string &s, const string &f) {
    if (f.empty()) return {};
    int m = f.size();
    vector<int> pi = prefix_function(f + '\0' + s), ans;  // '\0' must not appear in f
    for (int i = 2 * m; i < (int)pi.size(); i++) {
        if (pi[i] == m) ans.push_back(i - 2 * m);
    }
    return ans;
}

// Booth's algorithm for the lexicographically smallest rotation in O(n)
//   Booth(s)   stores s, O(n)
//   run()      start index of the lexicographically smallest rotation of s, O(n)
struct Booth {
    string s;
    Booth(const string &s): s(s) {}
    int run() {
        string s = this->s + this->s;
        int n = s.length(), i, j, k = 0;
        vector<int> f(n, -1);
        for (j = 1; j < n; j++) {
            i = f[j - k - 1];
            while (i != -1 && s[j] != s[k + i + 1]) {
                if (s[j] < s[k + i + 1]) k = j - i - 1;
                i = f[i];
            }
            if (i == -1 && s[j] != s[k + i + 1]) {
                if (s[j] < s[k + i + 1]) k = j;
                f[j - k] = -1;
            }
            else f[j - k] = i + 1;
        }
        return k;
    }
};

// Z function, O(n): z[i] = length of the longest common prefix of s and s[i..]; z[0] = n
vector<int> z_function(const string &s) {
    int n = s.size();
    vector<int> z(n, 0);
    if (n) z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

// trie over sequences of any comparable type, L = sequence length
//   insert(s)           add the sequence s, O(L log alphabet)
//   count_matches(s)    number of inserted sequences equal to s, O(L log alphabet)
//   count_prefixes(s)   number of inserted sequences with prefix s, O(L log alphabet)
template <class S>
struct Trie {
    using T = typename S::value_type;
    struct Node {
        map<T, int> next;
        int prefixes = 0, words = 0;
    };
    vector<Node> t;

    Trie(): t(1) {}

    void insert(const S &s) {
        int cur = 0;
        t[cur].prefixes++;
        for (const T &c : s) {
            auto it = t[cur].next.find(c);
            int nx;
            if (it == t[cur].next.end()) {
                nx = t.size();
                t[cur].next[c] = nx;
                t.emplace_back();
            } else {
                nx = it->second;
            }
            cur = nx;
            t[cur].prefixes++;
        }
        t[cur].words++;
    }

    int find_node(const S &s) const {
        int cur = 0;
        for (const T &c : s) {
            auto it = t[cur].next.find(c);
            if (it == t[cur].next.end()) return -1;
            cur = it->second;
        }
        return cur;
    }

    int count_matches(const S &s) const {
        int v = find_node(s);
        return v == -1 ? 0 : t[v].words;
    }

    int count_prefixes(const S &s) const {
        int v = find_node(s);
        return v == -1 ? 0 : t[v].prefixes;
    }
};

// persistent binary trie: max xor against a range of an append-only array of values in [0, 2^BITS)
//   insert(x)          append x, O(BITS)
//   max_xor(l, r, x)   largest x ^ a[i] over i in [l, r); requires l < r, O(BITS)
template <int BITS = 30>
struct PersistentXorTrie {
    struct Node { int ch[2], cnt; };
    vector<Node> t;  // t[0] is the empty node
    vector<int> roots;

    PersistentXorTrie(): t(1, Node{{0, 0}, 0}), roots(1, 0) {}

    void insert(int x) {
        int prev = roots.back();
        t.push_back(t[prev]);
        int cur = t.size() - 1;
        roots.push_back(cur);
        t[cur].cnt++;
        for (int i = BITS - 1; i >= 0; i--) {
            int b = x >> i & 1;
            prev = t[prev].ch[b];
            t.push_back(t[prev]);
            int nx = t.size() - 1;
            t[cur].ch[b] = nx;
            t[nx].cnt++;
            cur = nx;
        }
    }

    int max_xor(int l, int r, int x) const {
        int a = roots[l], b = roots[r], res = 0;
        for (int i = BITS - 1; i >= 0; i--) {
            int want = (x >> i & 1) ^ 1;
            if (t[t[b].ch[want]].cnt - t[t[a].ch[want]].cnt > 0) res |= 1 << i;
            else want ^= 1;
            a = t[a].ch[want];
            b = t[b].ch[want];
        }
        return res;
    }
};

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

// Aho-Corasick automaton: KMP for many patterns over the alphabet [BASE, BASE + ALPHA)
//   add(s)          add pattern s, O(|s|)
//   build()         compute the fail links; call after every add, O(nodes * ALPHA)
//   count(text)     total occurrences of all patterns in text, counted with multiplicity, O(|text|)
template <int ALPHA = 26, char BASE = 'a'>
struct AhoCorasick {
    vector<array<int, ALPHA>> next;
    vector<int> fail;
    vector<ll> words;

    AhoCorasick() { new_node(); }

    int new_node() {
        array<int, ALPHA> a;
        a.fill(-1);
        next.push_back(a);
        fail.push_back(0);
        words.push_back(0);
        return next.size() - 1;
    }

    void add(const string &s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - BASE;
            if (next[v][c] == -1) {
                int u = new_node();
                next[v][c] = u;
            }
            v = next[v][c];
        }
        words[v]++;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < ALPHA; c++) {
            int &u = next[0][c];
            if (u == -1) u = 0;
            else q.push(u);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            words[v] += words[fail[v]];
            for (int c = 0; c < ALPHA; c++) {
                int &u = next[v][c];
                if (u == -1) {
                    u = next[fail[v]][c];
                } else {
                    fail[u] = next[fail[v]][c];
                    q.push(u);
                }
            }
        }
    }

    ll count(const string &text) const {
        ll res = 0;
        int v = 0;
        for (char ch : text) {
            v = next[v][ch - BASE];
            res += words[v];
        }
        return res;
    }
};

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

// polynomial rolling hash mod 2^61 - 1 with a random base, shared by all objects so hashes are comparable
//   RollingHash(s)   prefix hashes of s, O(n)
//   get(l, r)        hash of s[l..r), O(1)
struct RollingHash {
    static constexpr unsigned long long MOD = (1ULL << 61) - 1;
    static inline unsigned long long base = mt19937_64(chrono::steady_clock::now().time_since_epoch().count())() % (MOD - 1000) + 500;
    vector<unsigned long long> h, pw;

    static unsigned long long mul(unsigned long long a, unsigned long long b) {
        unsigned __int128 t = (unsigned __int128)a * b;
        unsigned long long x = (t & MOD) + (unsigned long long)(t >> 61);
        return x >= MOD ? x - MOD : x;
    }

    RollingHash(const string &s): h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        for (int i = 0; i < (int)s.size(); i++) {
            h[i + 1] = mul(h[i], base) + (unsigned char)s[i] + 1;
            if (h[i + 1] >= MOD) h[i + 1] -= MOD;
            pw[i + 1] = mul(pw[i], base);
        }
    }

    unsigned long long get(int l, int r) const {
        unsigned long long x = h[r] + MOD - mul(h[l], pw[r - l]);
        return x >= MOD ? x - MOD : x;
    }
};

// Manacher's algorithm, O(n); returns {d1, d2}
// d1[i] = number of odd palindromes centered at i, so the longest is s[i - d1[i] + 1 .. i + d1[i] - 1]
// d2[i] = number of even palindromes whose right center is i, so the longest is s[i - d2[i] .. i + d2[i] - 1]
pair<vector<int>, vector<int>> manacher(const string &s) {
    int n = s.size();
    vector<int> d1(n), d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 1 : min(d1[l + r - i], r - i + 1);
        while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) k++;
        d1[i] = k;
        if (i + k - 1 > r) l = i - k + 1, r = i + k - 1;
    }
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = i > r ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) k++;
        d2[i] = k;
        if (i + k - 1 > r) l = i - k, r = i + k - 1;
    }
    return {d1, d2};
}

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
            } else {
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
