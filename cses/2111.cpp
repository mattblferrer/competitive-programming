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

using cd = complex<double>;
const ll NTT_MOD = 998'244'353, NTT_ROOT = 3;

// in-place FFT (inverse FFT if invert, including the 1/n scaling); a.size() must be a power of 2, O(n log n)
void fft(vector<cd> &a, bool invert = false) {
    int n = a.size();
    assert(n > 0 && (n & (n - 1)) == 0);
    static vector<cd> rt(2, 1);  // rt[k + j] = e^(i * pi * j / k) for each power of 2 k, 0 <= j < k
    for (static int k = 2; k < n; k *= 2) {
        rt.resize(n);
        for (int j = 0; j < k; j++) rt[k + j] = cd(polar(1.0L, acosl(-1) * j / k));  // long double for accuracy
    }
    for (int i = 1, j = 0; i < n; i++) {  // bit-reversal permutation
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                cd z = rt[k + j] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
    if (invert) {
        reverse(a.begin() + 1, a.end());
        for (cd &x : a) x /= n;
    }
}

// product of integer polynomials a and b, O((n + m) log(n + m))
// exact while (sum a[i]^2 + sum b[i]^2) * log2(n + m) < ~9e14; use ntt_multiply for results mod 998244353
vector<ll> multiply(const vector<ll> &a, const vector<ll> &b) {
    if (a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1, n = 1;
    while (n < need) n <<= 1;
    vector<cd> in(n), out(n);
    for (int i = 0; i < (int)a.size(); i++) in[i].real(a[i]);
    for (int i = 0; i < (int)b.size(); i++) in[i].imag(b[i]);
    fft(in);
    for (cd &x : in) x *= x;  // (A + iB)^2 = A^2 - B^2 + 2iAB, so AB is recoverable from one transform
    for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    vector<ll> res(need);
    for (int i = 0; i < need; i++) res[i] = llround(imag(out[i]) / (4 * n));
    return res;
}

void solve() {
    ll k, n, m;
    cin >> k >> n >> m;
    vector<ll> a(k + 1), b(k + 1);
    for (ll i = 1; i <= n; i++) {
        ll aw;
        cin >> aw;
        a[aw]++;
    }
    for (ll i = 1; i <= m; i++) {
        ll bw;
        cin >> bw;
        b[bw]++;
    }

    vector<ll> w = multiply(a, b);
    for (ll i = 2; i <= 2 * k; i++) cout << w[i] << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);

    int t = 1;
    // cin >> t;  // comment out for single test
    while (t--) solve();
}
