// Contents
//   SAT             SAT solver (DPLL with watched literals); variables are 1..n, literal -x means "not x"

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
