// Contents
//   find_cycle           Floyd's cycle finding on x0, f(x0), f(f(x0)), ...
//   lis                  indices of a longest strictly increasing subsequence of a, O(n log n)
//   date_to_int          day number (Julian day) of a Gregorian date, O(1)
//   int_to_date          Gregorian date of a day number, O(1)
//   int_to_day           day of the week of a day number, 0 = Monday, O(1)
//   cur_time             current CPU time in seconds, O(1)
//   simulated_annealing  simulated annealing example
//   read_int             reads the next integer from stdin into x, false at end of input, O(digits)
//   next_bit_perm        next larger integer with the same number of set bits; requires x > 0, O(1)
//   is_square            true if x is a perfect square, O(1)
//   simpson              numeric integral of f over [a, b] by Simpson's rule, O(steps); steps must be even

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// Floyd's cycle finding on x0, f(x0), f(f(x0)), ...: returns {mu, lambda} (tail length, cycle length), O(mu + lambda)
template <class T, class F>
pair<int, int> find_cycle(T x0, F f) {
    T t = f(x0), h = f(t);
    int mu = 0, lam = 1;
    while (t != h) t = f(t), h = f(f(h));
    h = x0;
    while (t != h) t = f(t), h = f(h), mu++;
    h = f(t);
    while (t != h) h = f(h), lam++;
    return {mu, lam};
}

// indices of a longest strictly increasing subsequence of a, O(n log n)
vector<int> lis(const vector<ll> &a) {
    int n = a.size();
    vector<int> seq, prev(n, -1), ans;  // seq[k] = index of the smallest tail of an increasing subsequence of length k + 1
    for (int i = 0; i < n; i++) {
        int k = partition_point(seq.begin(), seq.end(), [&](int j) { return a[j] < a[i]; }) - seq.begin();
        if (k) prev[i] = seq[k - 1];
        if (k == (int)seq.size()) seq.push_back(i);
        else seq[k] = i;
    }
    for (int at = seq.empty() ? -1 : seq.back(); at != -1; at = prev[at]) ans.push_back(at);
    reverse(ans.begin(), ans.end());
    return ans;
}

// day number (Julian day) of a Gregorian date, O(1)
int date_to_int(int y, int m, int d) {
    return 1461 * (y + 4800 + (m - 14) / 12) / 4 + 367 * (m - 2 - (m - 14) / 12 * 12) / 12
         - 3 * ((y + 4900 + (m - 14) / 12) / 100) / 4 + d - 32075;
}

// Gregorian date of a day number, O(1)
void int_to_date(int jd, int &y, int &m, int &d) {
    int x = jd + 68569;
    int n = 4 * x / 146097;
    x -= (146097 * n + 3) / 4;
    int i = (4000 * (x + 1)) / 1461001;
    x -= 1461 * i / 4 - 31;
    int j = 80 * x / 2447;
    d = x - 2447 * j / 80;
    x = j / 11;
    m = j + 2 - 12 * x;
    y = 100 * (n - 49) + i + x;
}

// day of the week of a day number, 0 = Monday, O(1)
int int_to_day(int jd) { return jd % 7; }

// current CPU time in seconds, O(1)
double cur_time() { return (double)clock() / CLOCKS_PER_SEC; }

// simulated annealing example: finds a permutation of 1..n with a large sum of |p[i] - p[i + 1]|, runs for the given seconds
// edit the initial solution, the mutation and the delta for other problems; returns the best score found
ll simulated_annealing(int n, double seconds) {
    if (n < 2) return 0;
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> rand_float(0.0, 1.0);
    uniform_int_distribution<int> rand_int(0, n - 2);
    vector<int> sol(n);
    iota(sol.begin(), sol.end(), 1);
    shuffle(sol.begin(), sol.end(), gen);
    ll score = 0;
    for (int i = 1; i < n; i++) score += abs(sol[i] - sol[i - 1]);
    ll best = score;
    double t0 = 100.0, t1 = 0.001, temp = t0, start = cur_time();
    for (int iters = 0; ; iters++) {
        if (!(iters & 15)) {
            double progress = (cur_time() - start) / seconds;
            if (progress > 1.0) break;
            temp = t0 * pow(t1 / t0, progress);
        }
        int a = rand_int(gen), delta = 0;  // try swapping sol[a] and sol[a + 1]
        if (a > 0) delta += abs(sol[a + 1] - sol[a - 1]) - abs(sol[a] - sol[a - 1]);
        if (a + 2 < n) delta += abs(sol[a] - sol[a + 2]) - abs(sol[a + 1] - sol[a + 2]);
        if (delta >= 0 || rand_float(gen) < exp(delta / temp)) {
            swap(sol[a], sol[a + 1]);
            score += delta;
            best = max(best, score);
        }
    }
    return best;
}

// reads the next integer from stdin into x, false at end of input, O(digits); don't mix with cin unless synced
bool read_int(ll &x) {
    int c = getchar();
    while (c != EOF && c != '-' && !isdigit(c)) c = getchar();
    if (c == EOF) return false;
    bool neg = c == '-';
    x = neg ? 0 : c - '0';
    while (isdigit(c = getchar())) x = x * 10 + c - '0';
    if (neg) x = -x;
    return true;
}

// next larger integer with the same number of set bits; requires x > 0, O(1)
ll next_bit_perm(ll x) {
    ll y = x & -x, z = x + y;
    return z | ((x ^ z) >> 2) / y;
}

// true if x is a perfect square, O(1)
bool is_square(ll x) {
    static const unsigned long long M = [] {
        unsigned long long m = 0;
        for (int i = 0; i < 64; i++) m |= 1ULL << (63 - (i * i) % 64);
        return m;
    }();  // bit 63 - r is set iff r is a square mod 64
    if (x < 0) return false;
    if (x == 0) return true;
    if (!((M << (x & 63)) >> 63)) return false;
    int c = __builtin_ctzll(x);
    if (c & 1) return false;
    x >>= c;
    if ((x & 7) != 1) return false;
    ll r = llroundl(sqrtl(x));
    return (unsigned long long)r * r == (unsigned long long)x;
}

// numeric integral of f over [a, b] by Simpson's rule, O(steps); steps must be even
template <class F>
ld simpson(F f, ld a, ld b, int steps = 1000000) {
    ld h = (b - a) / steps, s = f(a) + f(b);
    for (int i = 1; i < steps; i++) s += f(a + h * i) * ((i & 1) ? 4 : 2);
    return s * h / 3;
}
