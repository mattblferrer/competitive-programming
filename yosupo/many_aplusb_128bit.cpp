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

using i128 = __int128;
using u128 = unsigned __int128;

// decimal string of an __int128, including -2^127; the unsigned overload covers all of [0, 2^128), O(digits)
string to_string128(u128 x) {
    string s;
    do s += char('0' + x % 10); while (x /= 10);
    return string(s.rbegin(), s.rend());
}

string to_string128(i128 x) { return x < 0 ? "-" + to_string128(-(u128)x) : to_string128((u128)x); }

// __int128 from a decimal string with an optional sign; no overflow check, O(length)
i128 parse128(const string &s) {
    size_t i = s[0] == '-' || s[0] == '+';
    i128 x = 0;
    for (; i < s.size(); i++) x = x * 10 + (s[i] - '0');
    return s[0] == '-' ? -x : x;
}

ostream &operator<<(ostream &os, i128 x) { return os << to_string128(x); }
ostream &operator<<(ostream &os, u128 x) { return os << to_string128(x); }

istream &operator>>(istream &is, i128 &x) {
    string s;
    is >> s;
    if (is) x = parse128(s);
    return is;
}

void solve() {
    i128 a, b;
    cin >> a >> b;
    cout << a + b << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    cin >> t;  // comment out for single test
    while (t--) solve();
}
