// Contents
//   ternary_search_int   smallest x in [lo, hi] minimizing f, O(log(hi - lo)) calls to f; f must fall, then rise
//   ternary_search_real  x in [lo, hi] minimizing a real function that falls and then rises, O(iters) calls to f
//   parallel_binary_search  for each query, the first step count after which check(i) holds, O(log steps) replays

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// smallest x in [lo, hi] minimizing f, O(log(hi - lo)) calls to f;
// f must fall, then rise, and may only be flat at its minimum
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

// parallel binary search: for each query i < q, the smallest t in [0, steps] such that check(i) holds after
// apply(0), ..., apply(t - 1), or steps + 1 if it never does; check(i) must stay true once true. Every round calls
// reset(), replays the steps in order and checks each open query at its midpoint, so O(log steps) rounds of
// O(steps + q) calls (plus sorting the midpoints)
template <class Reset, class Apply, class Check>
vector<int> parallel_binary_search(int q, int steps, Reset reset, Apply apply, Check check) {
    vector<int> lo(q, 0), hi(q, steps + 1);
    while (true) {
        vector<pair<int, int>> todo;  // {mid, query}
        for (int i = 0; i < q; i++) if (lo[i] < hi[i]) todo.push_back({(lo[i] + hi[i]) / 2, i});
        if (todo.empty()) break;
        sort(todo.begin(), todo.end());
        reset();
        int done = 0;
        for (auto [mid, i] : todo) {
            while (done < mid) apply(done++);
            if (check(i)) hi[i] = mid;
            else lo[i] = mid + 1;
        }
    }
    return lo;
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
