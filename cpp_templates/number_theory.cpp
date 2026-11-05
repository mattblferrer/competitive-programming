#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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

// smallest primitive root mod prime m, O(sqrt(m) + g log^2 m) where g is the answer (small in practice)
ll primitive_root(ll m) {
    if (m == 2) return 1;
    vector<ll> fact;  // distinct prime factors of m - 1
    ll phi = m - 1, n = phi;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            fact.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) fact.push_back(n);
    for (ll x = 2; x < m; ++x) {
        bool ok = true;
        for (ll p : fact) if (binexp(x, phi / p, m) == 1) {
            ok = false; break;
        }
        if (ok) return x;
    }
    return -1;
}