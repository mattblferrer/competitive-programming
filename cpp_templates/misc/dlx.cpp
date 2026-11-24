// Contents
//   DLX             exact cover with dancing links (Algorithm X)

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;

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
