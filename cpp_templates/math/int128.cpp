// Contents
//   to_string128  decimal string of an __int128 (or unsigned __int128)
//   parse128      __int128 from a decimal string with an optional sign
//   operator<<    print __int128 and unsigned __int128 with cout or any ostream
//   operator>>    read __int128 with cin or any istream
//   gcd128        gcd of two __int128 (std::gcd needs gnu++ mode for __int128)
//   Frac          exact fraction with __int128 numerator and denominator, always reduced
//   mulmod        a * b mod m for m up to ~7.2e18 without __int128 (long double quotient), O(1)
//   powmod        a^e mod m for m up to ~7.2e18, using mulmod, O(log e)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;
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

// gcd of two __int128, always >= 0, O(log)
i128 gcd128(i128 a, i128 b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) a %= b, swap(a, b);
    return a;
}

// exact fraction p / q with __int128 parts, kept reduced with q > 0; +, -, *, / cancel before multiplying, so they only
// overflow if the reduced result needs more than 127 bits; comparisons cross-multiply, so p and q must stay below
// ~1.3e19 for them; 0 / 1 is zero, and a zero denominator is not checked
//   Frac(p, q)          p / q reduced, O(log)
//   +, -, *, /          (and +=, ...) exact arithmetic, O(log)
//   <, >, <=, >=, ==, !=  comparisons, O(1)
//   floor(), ceil()     floor and ceiling of p / q, O(1)
//   cout << f           prints p/q, or just p if q = 1
struct Frac {
    i128 p, q;

    Frac(i128 p = 0, i128 q = 1): p(p), q(q) {
        i128 g = gcd128(p, q);
        if (g) this->p /= g, this->q /= g;
        if (this->q < 0) this->p = -this->p, this->q = -this->q;
    }

    friend Frac operator+(const Frac &a, const Frac &b) {
        i128 g = gcd128(a.q, b.q);
        return Frac(a.p * (b.q / g) + b.p * (a.q / g), a.q / g * b.q);
    }
    friend Frac operator-(const Frac &a, const Frac &b) { return a + Frac(-b.p, b.q); }
    friend Frac operator*(const Frac &a, const Frac &b) {
        i128 g1 = gcd128(a.p, b.q), g2 = gcd128(b.p, a.q);  // nonzero, since q > 0
        return Frac((a.p / g1) * (b.p / g2), (a.q / g2) * (b.q / g1));
    }
    friend Frac operator/(const Frac &a, const Frac &b) { return a * Frac(b.q, b.p); }
    Frac &operator+=(const Frac &o) { return *this = *this + o; }
    Frac &operator-=(const Frac &o) { return *this = *this - o; }
    Frac &operator*=(const Frac &o) { return *this = *this * o; }
    Frac &operator/=(const Frac &o) { return *this = *this / o; }
    Frac operator-() const { return Frac(-p, q); }

    friend bool operator<(const Frac &a, const Frac &b) { return a.p * b.q < b.p * a.q; }
    friend bool operator>(const Frac &a, const Frac &b) { return b < a; }
    friend bool operator<=(const Frac &a, const Frac &b) { return !(b < a); }
    friend bool operator>=(const Frac &a, const Frac &b) { return !(a < b); }
    friend bool operator==(const Frac &a, const Frac &b) { return a.p == b.p && a.q == b.q; }
    friend bool operator!=(const Frac &a, const Frac &b) { return !(a == b); }

    i128 floor() const { return p / q - (p % q < 0); }
    i128 ceil() const { return p / q + (p % q > 0); }

    friend ostream &operator<<(ostream &os, const Frac &f) {
        os << f.p;
        if (f.q != 1) os << '/' << f.q;
        return os;
    }
};

// a * b mod m for 0 <= a, b < m <= 7.2e18 (about 2^62.6) without __int128: the quotient comes from a long double,
// and its error of one is fixed in 64-bit wraparound arithmetic; needs an 80-bit long double (g++ on x86, not MSVC)
// (unsigned __int128)a * b % m is the portable, slower alternative, O(1)
ull mulmod(ull a, ull b, ull m) {
    ll r = a * b - m * ull(1.L / m * a * b);
    return r + m * (r < 0) - m * (r >= (ll)m);
}

// a^e mod m for m up to ~7.2e18, using mulmod, O(log e)
ull powmod(ull a, ull e, ull m) {
    ull r = 1 % m;
    for (a %= m; e; e >>= 1, a = mulmod(a, a, m)) if (e & 1) r = mulmod(r, a, m);
    return r;
}
