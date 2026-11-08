#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

// SAT solver (DPLL with watched literals); variables are 1..n, literal -x means "not x"; exponential in the worst case
//   var()            create a new variable and return it, O(1)
//   clause(vars)     require at least one literal in vars to be true; call before solve, O(|vars| log |vars|)
//   assume(x)        set literal index x and propagate, false on a conflict
//   backtrack()      search over the remaining variables, true if satisfiable
//   solve()          true if satisfiable, call at most once
//   get_value(x)     value of variable x after a successful solve, O(1)
struct SAT {
    int n = 0;
    vector<int> cl, head, tail;
    vector<char> val;
    vector<pair<int, int>> trail;
    vector<vector<int>> watch, loc;

    static int idx(int x) { return (abs(x) - 1) * 2 + (x > 0); }

    int var() { return ++n; }

    void clause(const vector<int> &vars) {
        set<int> seen;
        for (int v : vars) {
            if (seen.count(idx(v) ^ 1)) return;  // always true
            seen.insert(idx(v));
        }
        head.push_back(cl.size());
        for (int v : seen) cl.push_back(v);
        tail.push_back((int)cl.size() - 2);
    }

    bool assume(int x) {
        if (val[x ^ 1]) return false;
        if (val[x]) return true;
        val[x] = true;
        trail.push_back({-1, x});
        for (int i = 0; i < (int)watch[x ^ 1].size(); i++) {
            int at = watch[x ^ 1][i], h = head[at], t = tail[at];
            trail.push_back({at, h});
            if (cl[t + 1] != (x ^ 1)) swap(cl[t], cl[t + 1]);
            while (h < t && val[cl[h] ^ 1]) h++;
            if ((head[at] = h) < t) {
                watch[cl[h]].push_back(watch[x ^ 1][i]);
                swap(watch[x ^ 1][i--], watch[x ^ 1].back());
                watch[x ^ 1].pop_back();
                swap(cl[head[at]++], cl[t + 1]);
            } else if (!assume(cl[t])) {
                return false;
            }
        }
        return true;
    }

    bool backtrack() {
        int v = trail.size(), x = -1;
        ll best = -1;
        for (int i = 0; i < n; i++) {
            if (val[2 * i] != val[2 * i + 1]) continue;
            ll s = 0, t = 0;
            for (int j = 0; j < 2; j++) {
                for (int c : loc[2 * i + j]) s += 1LL << max(0, 40 - tail[c] + head[c]);
                swap(s, t);
            }
            if (max(s, t) >= best) {
                best = max(s, t);
                x = 2 * i + (t >= s);
            }
        }
        if (best == -1 || (assume(x) && backtrack())) return true;
        while ((int)trail.size() != v) {
            auto [p, q] = trail.back();
            trail.pop_back();
            if (p == -1) val[q] = false;
            else head[p] = q;
        }
        return assume(x ^ 1) && backtrack();
    }

    bool solve() {
        val.assign(2 * n + 1, false);
        watch.assign(2 * n + 1, {});
        loc.assign(2 * n + 1, {});
        int m = head.size();
        for (int i = 0; i < m; i++) {
            if (head[i] == tail[i] + 2) return false;
            for (int at = head[i]; at < tail[i] + 2; at++) loc[cl[at]].push_back(i);
        }
        for (int i = 0; i < m; i++) {
            if (head[i] < tail[i] + 1) {
                for (int t = 0; t < 2; t++) watch[cl[tail[i] + t]].push_back(i);
            }
        }
        for (int i = 0; i < m; i++) {
            if (head[i] == tail[i] + 1 && !assume(cl[head[i]])) return false;
        }
        return backtrack();
    }

    bool get_value(int x) const { return val[idx(x)]; }
};

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

// two-phase simplex: maximize c^T x subject to A x <= b, x >= 0; A is m x n, O(pivots * n * m)
//   Simplex(A, b, c)   set up the tableau, O(nm)
//   pivot(r, s)        pivot on row r, column s, O(nm)
//   run(phase)         pivot until optimal; false if unbounded
//   solve(x)           optimal value (and x), +infinity if unbounded, -infinity if infeasible
struct Simplex {
    static constexpr ld EPS = 1e-9;
    int m, n;
    vector<int> B, N;
    vector<vector<ld>> D;

    Simplex(const vector<vector<ld>> &A, const vector<ld> &b, const vector<ld> &c)
        : m(b.size()), n(c.size()), B(m), N(n + 1), D(m + 2, vector<ld>(n + 2)) {
        for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }

    void pivot(int r, int s) {
        ld inv = 1.0L / D[r][s];
        for (int i = 0; i < m + 2; i++) {
            if (i == r) continue;
            for (int j = 0; j < n + 2; j++) if (j != s) D[i][j] -= D[r][j] * D[i][s] * inv;
        }
        for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
        for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
        D[r][s] = inv;
        swap(B[r], N[s]);
    }

    bool run(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1) continue;
                if (s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s])) s = j;
            }
            if (D[x][s] > -EPS) return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < EPS) continue;
                if (r == -1) {
                    r = i;
                    continue;
                }
                ld cur = D[i][n + 1] / D[i][s], low = D[r][n + 1] / D[r][s];
                if (cur < low || (cur == low && B[i] < B[r])) r = i;
            }
            if (r == -1) return false;
            pivot(r, s);
        }
    }

    ld solve(vector<ld> &x) {
        int r = 0;
        for (int i = 1; i < m; i++) if (D[i][n + 1] < D[r][n + 1]) r = i;
        if (m > 0 && D[r][n + 1] < -EPS) {
            pivot(r, n);
            if (!run(1) || D[m + 1][n + 1] < -EPS) return -numeric_limits<ld>::infinity();
            for (int i = 0; i < m; i++) {
                if (B[i] != -1) continue;
                int s = -1;
                for (int j = 0; j <= n; j++)
                    if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s])) s = j;
                pivot(i, s);
            }
        }
        if (!run(2)) return numeric_limits<ld>::infinity();
        x = vector<ld>(n);
        for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};

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

// exact cover with dancing links (Algorithm X): choose rows so every column is covered exactly once; exponential in the worst case
//   DLX(cols)          empty matrix with columns 0..cols-1, O(cols)
//   add_row(id, cs)    add a row covering the distinct columns cs; id is what solutions report, O(|cs|)
//   cover(c)           remove internal column c and the rows using it
//   uncover(c)         undo cover(c)
//   search(f)          call f(rows) for each solution until f returns true; true if f stopped the search
//   solve(ans)         store one solution's row ids in ans; false if there is none
//   count()            total number of solutions
struct DLX {
    int cols;
    vector<int> L, R, U, D, col, row, sz, cur;  // node 0 is the header, nodes 1..cols are the column heads

    DLX(int cols = 0): cols(cols), sz(cols + 1, 0) {
        for (int i = 0; i <= cols; i++) {
            L.push_back(i == 0 ? cols : i - 1);
            R.push_back(i == cols ? 0 : i + 1);
            U.push_back(i);
            D.push_back(i);
            col.push_back(i);
            row.push_back(-1);
        }
    }

    void add_row(int id, const vector<int> &cs) {
        int first = -1;
        for (int c0 : cs) {
            int c = c0 + 1, x = L.size();
            U.push_back(U[c]);
            D.push_back(c);
            D[U[c]] = x;
            U[c] = x;
            col.push_back(c);
            row.push_back(id);
            sz[c]++;
            if (first == -1) {
                L.push_back(x);
                R.push_back(x);
                first = x;
            } else {
                L.push_back(L[first]);
                R.push_back(first);
                R[L[first]] = x;
                L[first] = x;
            }
        }
    }

    void cover(int c) {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        for (int i = D[c]; i != c; i = D[i]) {
            for (int j = R[i]; j != i; j = R[j]) {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                sz[col[j]]--;
            }
        }
    }

    void uncover(int c) {
        for (int i = U[c]; i != c; i = U[i]) {
            for (int j = L[i]; j != i; j = L[j]) {
                sz[col[j]]++;
                U[D[j]] = j;
                D[U[j]] = j;
            }
        }
        L[R[c]] = c;
        R[L[c]] = c;
    }

    template <class F>
    bool search(F &f) {
        if (R[0] == 0) return f(cur);
        int c = R[0];
        for (int j = R[0]; j != 0; j = R[j]) if (sz[j] < sz[c]) c = j;  // fewest choices first
        cover(c);
        bool found = false;
        for (int r = D[c]; r != c && !found; r = D[r]) {
            cur.push_back(row[r]);
            for (int j = R[r]; j != r; j = R[j]) cover(col[j]);
            found = search(f);
            for (int j = L[r]; j != r; j = L[j]) uncover(col[j]);
            cur.pop_back();
        }
        uncover(c);
        return found;
    }

    bool solve(vector<int> &ans) {
        auto f = [&](const vector<int> &rows) {
            ans = rows;
            return true;
        };
        return search(f);
    }

    ll count() {
        ll total = 0;
        auto f = [&](const vector<int> &) {
            total++;
            return false;
        };
        search(f);
        return total;
    }
};
