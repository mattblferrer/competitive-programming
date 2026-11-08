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
