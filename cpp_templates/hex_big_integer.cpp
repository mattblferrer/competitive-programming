#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// arbitrary-precision signed hex integer (addition and subtraction)
// n below = number of hex digits
//   HexBigInt(a)           construct from long long, O(log a)
//   HexBigInt(s)           construct from a hex string, O(len)
//   read(s)                parse a hex string with optional '-', case-insensitive, O(len)
//   trim()                 remove leading zeros and make 0 non-negative, O(n)
//   size()                 number of hex digits (0 for zero), O(1)
//   abs_val()              absolute value, O(n)
//   abs_less(a, b)         |a| < |b|, O(n)
//   add_abs(a, b)          |a| + |b| with the sign of a, O(n)
//   sub_abs(a, b)          |a| - |b| with the sign of a; requires |a| >= |b|, O(n)
//   <, >, <=, >=, ==, !=   comparisons, O(n)
//   -x                     negation, O(n)
//   +, -, +=, -=           signed addition and subtraction, O(n)
//   x[idx]                 idx-th most significant digit, O(1)
//   cin >> x               read a hex number from a stream, O(len)
//   cout << x              write in hex to a stream, O(n)
struct HexBigInt {
    vector<int> d;  // hex digits, little-endian; zero is stored as empty d
    bool sign = false;  // false = pos, true = neg

    HexBigInt(ll a = 0) {
        if (a < 0) {
            sign = true;
            a = -a;
        }
        while (a > 0) {
            d.push_back(a % 16);
            a /= 16;
        }
    }
    HexBigInt(const string &s) { read(s); }
    HexBigInt(const char *s) { read(s); }

    void read(const string &s) {
        d.clear();
        sign = !s.empty() && s[0] == '-';
        for (int i = (int)s.size() - 1; i >= (int)sign; i--) {
            char c = toupper(s[i]);
            d.push_back(isdigit(c) ? c - '0' : c - 'A' + 10);
        }
        trim();
    }
    void trim() {
        while (!d.empty() && d.back() == 0) d.pop_back();
        if (d.empty()) sign = false;
    }
    int size() const {
        return d.size();
    }
    HexBigInt abs_val() const {
        HexBigInt c = *this;
        c.sign = false;
        return c;
    }
    static bool abs_less(const HexBigInt &a, const HexBigInt &b) {
        if (a.size() != b.size()) return a.size() < b.size();
        for (int i = a.size() - 1; i >= 0; i--) {
            if (a.d[i] != b.d[i]) return a.d[i] < b.d[i];
        }
        return false;
    }
    static HexBigInt add_abs(HexBigInt a, const HexBigInt &b) {
        int n = max(a.size(), b.size());
        a.d.resize(n + 1, 0);
        for (int i = 0; i < b.size(); i++) a.d[i] += b.d[i];
        for (int i = 0; i < n; i++) {
            if (a.d[i] > 15) {
                a.d[i] -= 16;
                a.d[i + 1]++;
            }
        }
        a.trim();
        return a;
    }
    static HexBigInt sub_abs(HexBigInt a, const HexBigInt &b) {
        for (int i = 0; i < b.size(); i++) a.d[i] -= b.d[i];
        for (int i = 0; i < a.size() - 1; i++) {
            if (a.d[i] < 0) {
                a.d[i] += 16;
                a.d[i + 1]--;
            }
        }
        a.trim();
        return a;
    }

    friend bool operator==(const HexBigInt &a, const HexBigInt &b) {
        return a.sign == b.sign && a.d == b.d;
    }
    friend bool operator!=(const HexBigInt &a, const HexBigInt &b) {
        return !(a == b);
    }
    friend bool operator<(const HexBigInt &a, const HexBigInt &b) {
        if (a.sign != b.sign) return a.sign;
        return a.sign ? abs_less(b, a) : abs_less(a, b);
    }
    friend bool operator>(const HexBigInt &a, const HexBigInt &b) {
        return b < a;
    }
    friend bool operator>=(const HexBigInt &a, const HexBigInt &b) {
        return !(a < b);
    }
    friend bool operator<=(const HexBigInt &a, const HexBigInt &b) {
        return !(a > b);
    }
    HexBigInt operator-() const {
        HexBigInt c = *this;
        if (!c.d.empty()) c.sign = !c.sign;
        return c;
    }
    friend HexBigInt operator+(const HexBigInt &a, const HexBigInt &b) {
        if (a.sign == b.sign) return add_abs(a, b);
        if (abs_less(a, b)) return sub_abs(b, a);
        return sub_abs(a, b);
    }
    friend HexBigInt operator-(const HexBigInt &a, const HexBigInt &b) {
        return a + (-b);
    }
    friend HexBigInt &operator+=(HexBigInt &a, const HexBigInt &b) {
        return a = a + b;
    }
    friend HexBigInt &operator-=(HexBigInt &a, const HexBigInt &b) {
        return a = a - b;
    }
    int operator[](const int idx) const {
        return d[d.size() - idx - 1];
    }
    friend istream &operator>>(istream &in, HexBigInt &a) {
        string s;
        in >> s;
        a.read(s);
        return in;
    }
    friend ostream &operator<<(ostream &out, const HexBigInt &a) {
        if (a.d.empty()) return out << '0';
        if (a.sign) out << '-';
        for (int i = a.size() - 1; i >= 0; i--) {
            out << "0123456789ABCDEF"[a.d[i]];
        }
        return out;
    }
};
