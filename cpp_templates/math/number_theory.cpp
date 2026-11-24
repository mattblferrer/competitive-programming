// Contents
//   binexp              a^b mod mod, O(log b)
//   modinv_p            inverse of a mod prime p (Fermat), O(log p)
//   extended_euclidean  returns g = gcd(a, b) and sets x, y so that ax + by = g, O(log min(a, b))
//   modinv              inverse of a mod any modulus, -1 if gcd(a, mod) != 1, O(log mod)
//   discrete_log        smallest x >= 0 with a^x = b (mod m), -1 if none; baby-step giant-step, O(sqrt(m))
//   is_prime            trial-division primality test, O(sqrt(n))
//   sieve               Sieve of Eratosthenes: prime[i] for 0 <= i <= n, O(n log log n)
//   sum_of_divisors     sum of the divisors of n, mod mod, O(sqrt(n))
//   miller_rabin        deterministic Miller-Rabin for any n fitting in ll, O(log n) multiplications
//   mobius_sieve        Mobius function mu[0..n], O(n log log n)
//   gcd_subset_count    cnt[g] = number of non-empty subsets of a with gcd exactly g, mod mod
//   divisor_transform   sum over multiples or divisors of each index (and its inverse), one prime at a time
//   gcd_convolution     c[k] = sum of a[i] * b[j] over all gcd(i, j) == k (or lcm(i, j) == k), 1-indexed
//   totient             Euler's totient phi(n), O(sqrt n)
//   mod_solver          solves a * x = b (mod m), m > 0: returns {x, M} meaning all solutions are x mod M
//   diophantine         integers x, y with a * x + b * y = c, nullopt if none; prefers y > 0
//   crt                 solves x = b1 (mod m1), x = b2 (mod m2), m1, m2 > 0: returns {x, lcm}, nullopt if none
//   super_crt           solves a[i] * x = b[i] (mod m[i]) for every i
//   josephus            survivor (0-indexed) among n people when every k-th is removed
//   spf_sieve           smallest prime factor of every number up to n (linear sieve); spf[0] = spf[1] = 0, O(n)
//   factorize_spf       prime factorization of x >= 1 as {prime, exponent} pairs in increasing order
//   pollard_rho         a nontrivial factor of a composite n (Pollard's rho, Brent's variant)
//   factorize           prime factors of n >= 1 in increasing order, with repeats; n can be any ll
//   primitive_root      smallest primitive root mod prime m, any m fitting in ll; uses factorize above
//   floor_sum           sum of floor((a * i + b) / m) for i in [0, n); m > 0, a and b can be negative, O(log m)
//   mod_sqrt            a square root of a mod the prime p (Tonelli-Shanks), the smaller of the two
//   kth_root_floor      floor(a^(1/k)) for any a < 2^64 and k >= 1, O(k)
//   kth_root_mod        some x with x^k = a (mod p) for a prime p, -1 if none (Adleman-Manders-Miller)
//   bernoulli           Bernoulli numbers B[0..n] mod a prime p > n + 1, with B[1] = -1/2, O(n^2)
//   tetration           a^^b = a^(a^(...^a)) (b copies of a) mod m, with a^^0 = 1 and 0^0 = 1
//   count_squarefree    number of squarefree integers in [1, n], n up to 1e18, O(n^(2/5))

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using ull = unsigned long long;

// a^b mod mod, O(log b)
ll binexp(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b % 2) {
            ans = (ans * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return ans;
}

// inverse of a mod prime p (Fermat), O(log p)
ll modinv_p(ll a, ll p) {
    return binexp(a, p - 2, p);
}

// returns g = gcd(a, b) and sets x, y so that ax + by = g, O(log min(a, b))
ll extended_euclidean(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll gcd = extended_euclidean(b, a % b, y, x);
    y -= (a / b) * x;
    return gcd;
}

// inverse of a mod any modulus, -1 if gcd(a, mod) != 1, O(log mod)
ll modinv(ll a, ll mod) {
    ll x, y;
    ll gcd = extended_euclidean(a, mod, x, y);
    if (gcd != 1) return -1;  // doesn't exist
    return (x % mod + mod) % mod;
}

// smallest x >= 0 with a^x = b (mod m), -1 if none; baby-step giant-step, O(sqrt(m))
ll discrete_log(ll a, ll b, ll m) {
    a %= m, b %= m;
    ll k = 1LL, add = 0LL, g;
    while ((g = gcd(a, m)) > 1) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g, m /= g, ++add;
        k = (k * 1LL * a / g) % m;
    }

    ll n = sqrtl(m) + 1;
    ll an = 1LL;
    for (ll i = 0; i < n; ++i)
        an = (an * 1LL * a) % m;

    unordered_map<ll, ll> vals;
    for (ll q = 0, cur = b; q <= n; q++) {
        vals[cur] = q;
        cur = (cur * 1LL * a) % m;
    }

    for (ll p = 1, cur = k; p <= n; p++) {
        cur = (cur * 1LL * an) % m;
        if (vals.count(cur)) {
            ll ans = n * p - vals[cur] + add;
            return ans;
        }
    }
    return -1;
}

// trial-division primality test, O(sqrt(n))
bool is_prime(ll n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return n > 1;
}

// Sieve of Eratosthenes: prime[i] for 0 <= i <= n, O(n log log n)
void sieve(vector<bool> &prime, ll n) {
    prime.assign(n + 1, true);
    prime[0] = prime[1] = false;
    for (ll i = 2; i * i <= n; i++) {
        if (prime[i]) {
            for (ll j = i * i; j <= n; j += i) {
                prime[j] = false;
            }
        }
    }
}

// sum of the divisors of n, mod mod, O(sqrt(n))
ll sum_of_divisors(ll n, ll mod) {
    ll ans = 1;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;
        ll sum = 1, pow = 1;  // 1 + i + i^2 + ... + i^e
        while (n % i == 0) {
            n /= i;
            pow = (pow * i) % mod;
            sum = (sum + pow) % mod;
        }
        ans = (ans * sum) % mod;
    }
    if (n > 1) ans = (ans * ((1 + n) % mod)) % mod;
    return ans % mod;
}

// deterministic Miller-Rabin for any n fitting in ll, O(log n) multiplications
bool miller_rabin(ll n) {
    if (n < 2) return false;
    for (ll p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    auto mul = [&](ll a, ll b) { return (ll)((__int128)a * b % n); };
    auto power = [&](ll a, ll e) {
        ll r = 1;
        for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
        return r;
    };
    ll d = n - 1;
    int s = __builtin_ctzll(d);
    d >>= s;
    for (ll base : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        ll a = base % n;
        if (a == 0) continue;  // this base says nothing about n
        ll x = power(a, d);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int i = 1; i < s && composite; i++) {
            x = mul(x, x);
            if (x == n - 1) composite = false;
        }
        if (composite) return false;
    }
    return true;
}

// Mobius function mu[0..n], O(n log log n)
vector<int> mobius_sieve(int n) {
    vector<int> mu(n + 1, 1);
    vector<char> composite(n + 1, false);
    if (n >= 0) mu[0] = 0;
    for (ll i = 2; i <= n; i++) {
        if (composite[i]) continue;
        for (ll j = i; j <= n; j += i) {
            if (j > i) composite[j] = true;
            mu[j] = -mu[j];
        }
        for (ll j = i * i; j <= n; j += i * i) mu[j] = 0;
    }
    return mu;
}

// cnt[g] = number of non-empty subsets of a with gcd exactly g, mod mod, O(MAX log MAX) where MAX = max(a)
vector<ll> gcd_subset_count(const vector<int> &a, ll mod) {
    int mx = a.empty() ? 0 : *max_element(a.begin(), a.end());
    vector<int> freq(mx + 1, 0);
    for (int x : a) freq[x]++;
    vector<ll> cnt(mx + 1, 0);
    for (int g = mx; g >= 1; g--) {
        ll multiples = 0, sub = 0;
        for (int j = g; j <= mx; j += g) {
            multiples += freq[j];
            if (j > g) sub += cnt[j];
        }
        cnt[g] = ((binexp(2, multiples, mod) - 1 - sub) % mod + mod) % mod;
    }
    return cnt;
}

// in place over a[1..n] (a[0] unused), one prime at a time; invert undoes it (Mobius inversion), O(n log log n)
// multiples = true: a[d] becomes the sum of a[k] over multiples k of d (for gcd_convolution)
// multiples = false: a[d] becomes the sum of a[k] over divisors k of d (for lcm_convolution)
template <class T>
void divisor_transform(vector<T> &a, bool multiples, bool invert = false) {
    int n = a.size() - 1;
    vector<bool> composite(n + 1);
    for (int p = 2; p <= n; p++) {
        if (composite[p]) continue;
        for (ll q = (ll)p * p; q <= n; q += p) composite[q] = true;
        if (multiples != invert) for (int i = n / p; i >= 1; i--) multiples ? a[i] += a[i * p] : a[i * p] -= a[i];
        else for (int i = 1; i <= n / p; i++) multiples ? a[i] -= a[i * p] : a[i * p] += a[i];
    }
}

// c[k] = sum of a[i] * b[j] over all gcd(i, j) == k (lcm(i, j) == k if lcm), 1-indexed, a.size() == b.size(); no division,
// so T can be any ring, O(n log log n)
template <class T>
vector<T> gcd_convolution(vector<T> a, vector<T> b, bool lcm = false) {
    divisor_transform(a, !lcm);
    divisor_transform(b, !lcm);
    for (int i = 1; i < (int)a.size(); i++) a[i] = a[i] * b[i];
    divisor_transform(a, !lcm, true);
    return a;
}

// Euler's totient phi(n), O(sqrt n)
ll totient(ll n) {
    ll tot = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) tot -= tot / i;
        while (n % i == 0) n /= i;
    }
    if (n > 1) tot -= tot / n;
    return tot;
}

// solves a * x = b (mod m), m > 0: returns {x, M} meaning all solutions are x mod M, nullopt if none, O(log m)
optional<pll> mod_solver(ll a, ll b, ll m) {
    a = (a % m + m) % m;
    b = (b % m + m) % m;
    ll x, y, g = extended_euclidean(a, m, x, y);
    if (b % g != 0) return nullopt;
    ll M = m / g;
    x = (x % M + M) % M;
    return pll((__int128)x * (b / g) % M, M);
}

// integers x, y with a * x + b * y = c, nullopt if none; prefers y > 0, O(log min(|a|, |b|))
optional<pll> diophantine(ll a, ll b, ll c) {
    if (a == 0 && b == 0) return c == 0 ? optional<pll>(pll(0, 0)) : nullopt;
    if (a == 0) return c % b == 0 ? optional<pll>(pll(0, c / b)) : nullopt;
    if (b == 0) return c % a == 0 ? optional<pll>(pll(c / a, 0)) : nullopt;
    ll x, y, g = extended_euclidean(a, b, x, y);
    if (c % g != 0) return nullopt;
    ll m = llabs(a / g);
    y = (__int128)((y % m + m) % m) * (((c / g) % m + m) % m) % m;
    if (y == 0) y = m;
    return pll((ll)(((__int128)c - (__int128)b * y) / a), y);
}

// solves x = b1 (mod m1), x = b2 (mod m2), m1, m2 > 0: returns {x, lcm}, nullopt if none; the lcm must fit in ll, O(log m)
optional<pll> crt(ll b1, ll m1, ll b2, ll m2) {
    b1 = (b1 % m1 + m1) % m1;
    b2 = (b2 % m2 + m2) % m2;
    ll p, q, g = extended_euclidean(m1, m2, p, q);
    if ((b2 - b1) % g != 0) return nullopt;
    ll step = m2 / g, M = m1 / g * m2;
    ll t = (__int128)(((b2 - b1) / g) % step + step) * ((p % step + step) % step) % step;
    return pll((ll)(((__int128)b1 + (__int128)m1 * t) % M), M);
}

// solves x = b[i] (mod m[i]) for every i: returns {x, lcm}, nullopt if none, O(n log m)
optional<pll> crt(const vector<ll> &b, const vector<ll> &m) {
    pll ans = {0, 1};
    for (int i = 0; i < (int)b.size(); i++) {
        auto cur = crt(ans.first, ans.second, b[i], m[i]);
        if (!cur) return nullopt;
        ans = *cur;
    }
    return ans;
}

// solves a[i] * x = b[i] (mod m[i]) for every i: returns {x, M} meaning all solutions are x mod M, nullopt if none, O(n log m)
optional<pll> super_crt(const vector<ll> &a, const vector<ll> &b, const vector<ll> &m) {
    pll ans = {0, 1};
    for (int i = 0; i < (int)a.size(); i++) {
        auto one = mod_solver(a[i], b[i], m[i]);
        if (!one) return nullopt;
        auto cur = crt(ans.first, ans.second, one->first, one->second);
        if (!cur) return nullopt;
        ans = *cur;
    }
    return ans;
}

// survivor (0-indexed) among n people when every k-th is removed, starting the count at person 0, O(k log n)
ll josephus(ll n, ll k) {
    if (n == 1) return 0;
    if (k == 1) return n - 1;
    if (n < k) return (josephus(n - 1, k) + k) % n;
    ll np = n - n / k;
    return k * ((josephus(np, k) + np - n % k % np) % np) / (k - 1);
}

// smallest prime factor of every number up to n (linear sieve); spf[0] = spf[1] = 0, O(n)
vector<int> spf_sieve(int n) {
    vector<int> spf(n + 1, 0), primes;
    for (int i = 2; i <= n; i++) {
        if (!spf[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || (ll)i * p > n) break;
            spf[i * p] = p;
        }
    }
    return spf;
}

// prime factorization of x >= 1 as {prime, exponent} pairs in increasing order; x must be within spf, O(log x)
vector<pair<int, int>> factorize_spf(int x, const vector<int> &spf) {
    vector<pair<int, int>> res;
    while (x > 1) {
        int p = spf[x], e = 0;
        while (x % p == 0) {
            x /= p;
            e++;
        }
        res.push_back({p, e});
    }
    return res;
}

// a nontrivial factor of a composite n (Pollard's rho, Brent's variant), O(n^(1/4) log n) expected; uses gcd in batches
ll pollard_rho(ll n) {
    if (n % 2 == 0) return 2;
    static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
    auto mul = [&](ll a, ll b) { return (ll)((__int128)a * b % n); };
    while (true) {
        ll c = gen() % (n - 1) + 1, y = gen() % n, x = y, ys = y, q = 1, g = 1;
        auto f = [&](ll v) { return (ll)(((__int128)v * v + c) % n); };
        for (ll r = 1; g == 1; r *= 2) {
            x = y;
            for (ll i = 0; i < r; i++) y = f(y);
            for (ll k = 0; k < r && g == 1; k += 128) {
                ys = y;
                for (ll i = 0; i < min<ll>(128, r - k); i++) {
                    y = f(y);
                    q = mul(q, llabs(x - y));
                }
                g = gcd(q, n);
            }
        }
        if (g == n) {  // the batch overshot: step through it one at a time
            do {
                ys = f(ys);
                g = gcd(llabs(x - ys), n);
            } while (g == 1);
        }
        if (g != n) return g;
    }
}

// prime factors of n >= 1 in increasing order, with repeats; n can be any ll, O(n^(1/4) log n) expected
vector<ll> factorize(ll n) {
    vector<ll> res;
    for (ll p = 2; p < 100 && p * p <= n; p++) {
        while (n % p == 0) {
            res.push_back(p);
            n /= p;
        }
    }
    function<void(ll)> go = [&](ll x) {
        if (x == 1) return;
        if (miller_rabin(x)) {
            res.push_back(x);
            return;
        }
        ll d = pollard_rho(x);
        go(d);
        go(x / d);
    };
    go(n);
    sort(res.begin(), res.end());
    return res;
}

// smallest primitive root mod prime m, any m fitting in ll; uses factorize above
// O(m^(1/4) log m + g log^2 m) expected, where g is the answer (small in practice)
ll primitive_root(ll m) {
    if (m == 2) return 1;
    auto mul = [&](ll a, ll b) { return (ll)((__int128)a * b % m); };  // a * b overflows ll once m > ~3e9
    auto power = [&](ll a, ll e) {
        ll r = 1;
        for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
        return r;
    };
    ll phi = m - 1;
    vector<ll> fact = factorize(phi);  // Pollard's rho; trial division is ~1e9 steps when m - 1 = 2 * prime
    fact.erase(unique(fact.begin(), fact.end()), fact.end());
    for (ll x = 2; x < m; x++) {
        bool ok = true;
        for (ll p : fact) if (power(x, phi / p) == 1) {
            ok = false; break;
        }
        if (ok) return x;
    }
    return -1;
}

// sum of floor((a * i + b) / m) for i in [0, n); m > 0, a and b can be negative, O(log m)
// the answer and a * n + b (after reducing a and b mod m) must fit in ll
// lattice points with A * x + B * y <= C, 0 <= x <= n, y >= 0 is floor_sum(n + 1, B, -A, C + B) when C - A * n >= 0
ll floor_sum(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    if (a < 0) {
        ll r = (a % m + m) % m;
        ans -= n * (n - 1) / 2 * ((r - a) / m);
        a = r;
    }
    if (b < 0) {
        ll r = (b % m + m) % m;
        ans -= n * ((r - b) / m);
        b = r;
    }
    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        ll y_max = a * n + b;
        if (y_max < m) break;
        n = y_max / m;
        b = y_max % m;
        swap(m, a);
    }
    return ans;
}

// a square root of a mod the prime p (Tonelli-Shanks), the smaller of the two; -1 if none exists; p below 2^31, O(log^2 p)
ll mod_sqrt(ll a, ll p) {
    a = (a % p + p) % p;
    if (a == 0 || p == 2) return a;
    if (binexp(a, (p - 1) / 2, p) != 1) return -1;
    ll r;
    if (p % 4 == 3) {
        r = binexp(a, (p + 1) / 4, p);
    } else {
        ll q = p - 1, z = 2;
        int s = 0;
        while (q % 2 == 0) {
            q /= 2;
            s++;
        }
        while (binexp(z, (p - 1) / 2, p) != p - 1) z++;
        int m = s;
        ll c = binexp(z, q, p), t = binexp(a, q, p);
        r = binexp(a, (q + 1) / 2, p);
        while (t != 1) {
            int i = 0;
            for (ll x = t; x != 1; x = x * x % p) i++;
            ll b = c;
            for (int j = 0; j < m - i - 1; j++) b = b * b % p;
            m = i;
            c = b * b % p;
            t = t * c % p;
            r = r * b % p;
        }
    }
    return min(r, p - r);
}

// floor(a^(1/k)) for any a < 2^64 and k >= 1, O(k)
ull kth_root_floor(ull a, ull k) {
    if (k == 1 || a <= 1) return a;
    if (k >= 64) return 1;
    auto fits = [&](ull x) {  // x^k <= a, without overflow
        ull r = 1;
        for (ull i = 0; i < k; i++) {
            if (r > a / x) return false;
            r *= x;
        }
        return true;
    };
    ull x = powl((ld)a, 1.0L / k);  // off by at most a few, fixed below
    while (!fits(x)) x--;
    while (fits(x + 1)) x++;
    return x;
}

// some x with x^k = a (mod p) for a prime p, -1 if none (Adleman-Manders-Miller); k >= 0, 0^0 = 1
// reduces to g-th roots for g = gcd(k, p - 1), then takes one q-th root per prime factor q of g
// O(log^2 p + sqrt(q) log p) per prime q dividing g (with multiplicity); uses modinv and factorize above
ll kth_root_mod(ll a, ll k, ll p) {
    auto mul = [&](ll x, ll y) { return (ll)((__int128)x * y % p); };
    auto power = [&](ll x, ll e) {
        ll r = 1;
        for (; e; e >>= 1, x = mul(x, x)) if (e & 1) r = mul(r, x);
        return r;
    };
    a = (a % p + p) % p;
    if (k == 0) return a == 1 ? 1 : -1;
    if (a == 0) return 0;
    ll g = gcd(k, p - 1), m = (p - 1) / g;
    if (power(a, m) != 1) return -1;
    a = power(a, modinv(k / g % m, m));  // now any x with x^g = a works
    auto root = [&](ll a, ll r) {  // some x with x^r = a, for a prime r dividing p - 1 and an r-th power a
        ll s = 0, t = p - 1;
        while (t % r == 0) t /= r, s++;
        ll rho = 2;
        while (power(rho, (p - 1) / r) == 1) rho++;  // any non-r-th power
        ll z = power(rho, t), zinv = power(z, p - 2);  // z generates the subgroup of order r^s
        ll x = power(a, t == 1 ? 0 : modinv(r % t, t));  // x^r = a * (an element of that subgroup)
        ll h = mul(a, power(power(x, r), p - 2));  // the correction: find h = z^e, then x * z^(e / r) works
        ll top = 1;
        for (ll i = 0; i < s - 1; i++) top *= r;
        ll gam = power(z, top), M = sqrtl(r) + 1;  // gam has order r; baby-step giant-step for its logs
        vector<pll> baby(M);
        for (ll j = 0, cur = 1; j < M; j++, cur = mul(cur, gam)) baby[j] = {cur, j};
        sort(baby.begin(), baby.end());
        ll giant = power(power(gam, M), p - 2);
        auto dlog = [&](ll y) {  // d in [0, r) with gam^d = y
            for (ll i = 0; i <= M; i++, y = mul(y, giant)) {
                auto it = lower_bound(baby.begin(), baby.end(), pll(y, LLONG_MIN));
                if (it != baby.end() && it->first == y) return i * M + it->second;
            }
            return -1LL;
        };
        ll e = 0;
        for (ll i = 0, ri = 1, rest = top; i < s; i++, ri *= r, rest /= r)  // e one base-r digit at a time
            e += dlog(power(mul(h, power(zinv, e)), rest)) * ri;
        return mul(x, power(z, e / r));
    };
    for (ll q : factorize(g)) a = root(a, q);
    return a;
}

// Bernoulli numbers B[0..n] mod a prime p > n + 1, p below 2^31, with B[1] = -1/2:
// x / (e^x - 1) = sum of B[i] x^i / i!; use B[1] = +1/2 for sum_{i=1..N} i^m. O(n^2)
// sum_{i=0..N-1} i^m = 1 / (m + 1) * sum_{j=0..m} C(m + 1, j) B[j] N^(m + 1 - j)
vector<ll> bernoulli(int n, ll p) {
    vector<ll> inv(n + 2, 1), B(n + 1, 0), row = {1, 1};  // row = C(m + 1, 0..m + 1)
    for (int i = 2; i <= n + 1; i++) inv[i] = (p - p / i) * inv[p % i] % p;
    B[0] = 1;
    for (int m = 1; m <= n; m++) {
        row.push_back(1);
        for (int j = m; j > 0; j--) row[j] = (row[j] + row[j - 1]) % p;
        ll s = 0;
        for (int j = 0; j < m; j++) s = (s + row[j] * B[j]) % p;
        B[m] = (p - s) % p * inv[m + 1] % p;
    }
    return B;
}

// a^^b = a^(a^(...^a)) (b copies of a) mod m, with a^^0 = 1 and 0^0 = 1; a, b >= 0, m >= 1
// a^n = a^(n mod phi(m) + phi(m)) (mod m) once n >= log2(m), so recurse on phi(m) until it reaches 1
// O(sqrt(m) log m); uses totient above
ll tetration(ll a, ll b, ll m) {
    const ll CAP = 64;  // above log2(m) for every m in ll
    auto power = [](ll x, ll e, ll md) {
        ll r = 1 % md;
        for (x %= md; e; e >>= 1, x = (ll)((__int128)x * x % md)) if (e & 1) r = (ll)((__int128)r * x % md);
        return r;
    };
    auto exact = [&](ll k) {  // min(a^^k, CAP)
        if (a == 0) return (ll)(k % 2 == 0);
        if (a == 1) return 1LL;
        ll v = 1;
        for (ll i = 0; i < k && v < CAP; i++) {
            ll r = 1;
            for (ll j = 0; j < v && r < CAP; j++) r = min(CAP, r * min(a, CAP));
            v = r;
        }
        return v;
    };
    function<ll(ll, ll)> go = [&](ll b, ll m) -> ll {
        if (m == 1) return 0;
        if (b == 0) return 1;
        ll n = exact(b - 1);
        if (n < CAP) return power(a, n, m);
        ll ph = totient(m);
        return power(a, go(b - 1, ph) + ph, m);
    };
    return go(b, m);
}

// number of squarefree integers in [1, n], n up to 1e18, O(n^(2/5)) time and memory; uses mobius_sieve above
// answer = sum of mu(d) floor(n / d^2): d <= D = n^(2/5) directly; for d > D, floor(n / d^2) < n / D^2,
// so that part is sum over i >= 1 of M(sqrt(n / i)) - M(D) while sqrt(n / i) > D, with M the Mertens function
ll count_squarefree(ll n) {
    auto isqrt = [](ll x) {
        ll r = sqrtl((ld)x);
        while (r * r > x) r--;
        while ((r + 1) * (r + 1) <= x) r++;
        return r;
    };
    ll D = min(isqrt(n), max(1LL, (ll)powl((ld)n, 0.4L)));
    vector<int> M = mobius_sieve(D);  // mu, then its prefix sums M[x] for x <= D
    ll ans = 0;
    for (ll d = 1; d <= D; d++) if (M[d]) ans += M[d] * (n / (d * d));
    for (ll d = 1; d <= D; d++) M[d] += M[d - 1];
    auto mertens = [&](ll x) -> ll {  // M(x) = 1 - sum_{k = 2..x} M(x / k); only x / m with x / m > D need recursion
        if (x <= D) return M[x];
        ll K = x / D;
        vector<ll> big(K + 1);  // big[m] = M(x / m)
        for (ll m = K; m >= 1; m--) {
            ll v = x / m, s = 1, k = 2;
            if (v <= D) {
                big[m] = M[v];
                continue;
            }
            for (; v / k > D; k++) s -= big[m * k];
            for (ll hi; k <= v; k = hi + 1) {  // blocks of k with the same v / k
                ll q = v / k;
                hi = v / q;
                s -= (hi - k + 1) * M[q];
            }
            big[m] = s;
        }
        return big[1];
    };
    for (ll i = 1;; i++) {
        ll x = isqrt(n / i);
        if (x <= D) break;
        ans += mertens(x) - M[D];
    }
    return ans;
}
