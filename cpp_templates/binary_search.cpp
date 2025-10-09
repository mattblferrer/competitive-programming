#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// replace f(m) with desired condition

ll left = -1, right = n;
while (right - left > 1) {
    ll mid = (left + right) / 2;
    if (f(m)) right = mid; 
    else left = mid; 
}