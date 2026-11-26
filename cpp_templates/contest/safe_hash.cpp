// Contents
//   SafeHash  hash for unordered_map / unordered_set that resists anti-hash tests
//   SafeMap   unordered_map using SafeHash
//   SafeSet   unordered_set using SafeHash
//   Zobrist   random 64-bit label per key: XOR / sum of labels hash sets / multisets, with prefix hashes

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;

// hash for unordered_map / unordered_set that anti-hash tests can't target, since the seed changes on every run
// works for integer keys and pairs of integers
//   splitmix64(x)    mixes the bits of x, O(1)
//   operator()(x)    hash of an integer, O(1)
//   operator()(p)    hash of a pair of integers, O(1)
struct SafeHash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static ull seed() {
        static const ull s = chrono::steady_clock::now().time_since_epoch().count();
        return s;
    }

    size_t operator()(ull x) const { return splitmix64(x + seed()); }

    size_t operator()(const pll &p) const {
        return splitmix64(splitmix64(p.first + seed()) ^ (p.second + 0x9e3779b97f4a7c15));
    }
};

template <class K, class V>
using SafeMap = unordered_map<K, V, SafeHash>;

template <class K>
using SafeSet = unordered_set<K, SafeHash>;

// Zobrist hashing of sets and multisets: every key gets a random 64-bit label, the XOR of the labels hashes a set
// (the keys present an odd number of times) and their sum mod 2^64 hashes a multiset; both update in O(1) and compare
// subarrays through prefix hashes, e.g. a[l, r) is a permutation of 1..r-l iff its sum hash is that of {1..r-l}
//   operator()(x)    label of key x, O(1) expected
//   xor_prefix(a)    h[i] = XOR of the labels of a[0, i), so the set hash of a[l, r) is h[r] ^ h[l], O(n)
//   sum_prefix(a)    h[i] = sum of the labels of a[0, i), so the multiset hash of a[l, r) is h[r] - h[l], O(n)
struct Zobrist {
    mt19937_64 rng{SafeHash::seed()};
    SafeMap<ll, ull> label;

    ull operator()(ll x) {
        auto [it, fresh] = label.try_emplace(x);
        if (fresh) it->second = rng();
        return it->second;
    }

    vector<ull> xor_prefix(const vector<ll> &a) {
        vector<ull> h(a.size() + 1);
        for (int i = 0; i < (int)a.size(); i++) h[i + 1] = h[i] ^ (*this)(a[i]);
        return h;
    }

    vector<ull> sum_prefix(const vector<ll> &a) {
        vector<ull> h(a.size() + 1);
        for (int i = 0; i < (int)a.size(); i++) h[i + 1] = h[i] + (*this)(a[i]);
        return h;
    }
};
