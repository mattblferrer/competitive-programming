#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct mint {
    long long val, M;

    mint(long long v = 0, const long long m = MOD) {
        this->M = m;
        val = v % M;
        if (val < 0) val += M;
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
    mint inverse() const { return mint(power(val, M - 2, M)); }
    mint operator+(const mint &other) const { return mint(val + other.val); }
    mint operator-(const mint &other) const { return mint(val - other.val); }
    mint operator*(const mint &other) const { return mint((__int128)val * other.val % M); }
    mint operator/(const mint &other) const { return *this * other.inverse(); }
    mint &operator+=(const mint &other) { *this = *this + other; return *this; }
    mint &operator-=(const mint &other) { *this = *this - other; return *this; }
    mint &operator*=(const mint &other) { *this = *this * other; return *this; }
    mint &operator/=(const mint &other) { *this = *this / other; return *this; }
    mint &operator++() {
        val = (val + 1) % M;
        return *this;
    }
    mint operator++(int) {
        mint tmp = *this;
        ++(*this);
        return tmp;
    }
    mint &operator--() {
        val = (val - 1 + M) % M;
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
        return mint(power(val, exp, M));
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

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];

    set<ll> a_set(a.begin(), a.end());
    ll d = a_set.size(), minus_one = 0, next_a = 0;
    for (ll i = 0; i < n; i++) {
        if (a[i] == -1) minus_one++;
    }
    for (ll i = 0; i < n - 1; i++) {
        if (a[i] + 1 == a[i + 1]) next_a++;
    }

    mint ans;
    if (minus_one) ans = mint(2).pow(n - d) * mint(next_a + 1);
    else ans = mint(2).pow(n - d);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}