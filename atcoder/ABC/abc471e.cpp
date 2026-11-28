#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 998244353;

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

mint choose(ll n, ll k) {
    if (k < 0) return mint(0);

    mint ans = 1;
    for (ll i = n - k + 1; i <= n; i++) ans *= mint(i);
    for (ll i = 1; i <= k; i++) ans /= mint(i);
    return ans;
}

void solve() {
    ll n, k;
    cin >> n >> k;
    mint nm = n, km = k;
    vector<mint> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    if (n == 1) {
        mint ans = a[0] * a[0];
        cout << ans << "\n";
        return;
    }

    mint sum_sqs = 0, sum_2 = 0;
    for (ll i = 0; i < n; i++) {
        sum_sqs += a[i] * a[i];
        sum_2 += a[i];
    }
    sum_2 *= sum_2;

    mint term1 = choose(n - 1, k - 1) * sum_sqs;
    mint term2 = choose(n - 2, k - 2) * (sum_2 - sum_sqs);
    mint ans = term1 + term2;
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}