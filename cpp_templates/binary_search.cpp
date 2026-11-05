#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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