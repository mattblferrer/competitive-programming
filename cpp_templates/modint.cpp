#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct mint {
    long long val, MOD;

    mint(long long v = 0, long long MOD) {
        this->MOD = MOD;
        val = v % MOD;
        if (val < 0) val += MOD;
    }
    static long long power(long long base, long long exp, long long mod) {
        base %= mod;
        if (base < 0) base += mod;
        long long result = 1;
        while (exp > 0) {
            if (exp & 1) result = result * base % mod;
            base = base * base % mod;
            exp >>= 1;
        }
        return result;
    }
    mint inverse() const { return mint(power(val, MOD - 2, MOD)); }
    mint operator+(const mint &other) const { return mint(val + other.val); }
    mint operator-(const mint &other) const { return mint(val - other.val); }
    mint operator*(const mint &other) const { return mint((__int128)val * other.val % MOD); }
    mint operator/(const mint &other) const { return *this * other.inverse(); }
    mint &operator+=(const mint &other) { *this = *this + other; return *this; }
    mint &operator-=(const mint &other) { *this = *this - other; return *this; }
    mint &operator*=(const mint &other) { *this = *this * other; return *this; }
    mint &operator/=(const mint &other) { *this = *this / other; return *this; }
    mint &operator++() {
        val = (val + 1) % MOD;
        return *this;
    }
    mint operator++(int) {
        mint tmp = *this;
        ++(*this);
        return tmp;
    }
    mint &operator--() {
        val = (val - 1 + MOD) % MOD;
        return *this;
    }
    mint operator--(int) {
        mint tmp = *this;
        --(*this);
        return tmp;
    }
    bool operator==(const mint &other) const { return val == other.val; }
    bool operator!=(const mint &other) const { return val != other.val; }
    mint pow(long long exp) const {
        return mint(power(val, exp, MOD));
    }
    friend ostream &operator<<(ostream &os, const mint &m) {
        os << m.val;
        return os;
    }
    friend istream &operator>>(istream &is, mint &m) {
        long long x;
        is >> x;
        m = mint(x);
        return is;
    }
};