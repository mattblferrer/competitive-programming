#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// smallest x in [lo, hi] minimizing f, O(log(hi - lo)) calls to f; f must fall, then rise, and may only be flat at its minimum
// to maximize, pass a function returning -f(x)
template <class F>
ll ternary_search_int(ll lo, ll hi, F f) {
    while (lo < hi) {
        ll m = lo + (hi - lo) / 2;
        if (f(m) <= f(m + 1)) hi = m;
        else lo = m + 1;
    }
    return lo;
}

// x in [lo, hi] minimizing a real function that falls and then rises, O(iters) calls to f
template <class F>
ld ternary_search_real(ld lo, ld hi, F f, int iters = 200) {
    for (int i = 0; i < iters; i++) {
        ld m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) <= f(m2)) hi = m2;
        else lo = m1;
    }
    return (lo + hi) / 2;
}

// finds the first m in [0, n) where f(m) is true (f must be monotone: false...false true...true)
// answer is right (n if f is never true), O(log n) calls to f
int main() {
    // replace "f(mid)" with the desired condition

    ll n;
    ll left = -1, right = n;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        if ("f(mid)") right = mid;
        else left = mid;
    }
}
