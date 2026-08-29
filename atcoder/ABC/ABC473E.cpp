#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

struct mint {
    long long val, M;

    mint(long long v = 0, long long m = MOD) {
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
    mint inverse() const { return mint(power(val, M - 2, M), M); }
    mint operator+(const mint &other) const { return mint(val + other.val, M); }
    mint operator-(const mint &other) const { return mint(val - other.val, M); }
    mint operator*(const mint &other) const { return mint((__int128)val * other.val % M, M); }
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
        return mint(power(val, exp, M), M);
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
    ll n, k;
    cin >> n >> k;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    map<ll, ll> seen;
    seen[0] = 0;
    mint sum(0, k);
    ll p = 0, ans = 0, curr = -1;
    for (ll i = 1; i <= n; i++) {
        sum += a[i];
        if ((seen.count(sum.val)) && (seen[sum.val] >= curr)) {
            ans++;
            mint ns(sum.val, k);
            seen.erase(sum.val);
            curr = i;
        }
        seen[sum.val] = i;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}