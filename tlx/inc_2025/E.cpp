#include<bits/stdc++.h>
using namespace std;

struct segtree {
    vector<array<int, 16>> t;
    int n;
    segtree(vector<array<int, 16>> &a, int n) : n(n) {
        t.resize(4*n);
        build(a, 1, 0, n-1);
    }

    void build(vector<array<int, 16>> &a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            pull(v);
        }
    }

    void pull(int v) {
        for (int i = 0; i < 16; i++)
            t[v][i] = t[v*2+1][t[v*2][i]];
    }

    void update(int v, int tl, int tr, int pos, array<int, 16> &val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v*2, tl, tm, pos, val);
            else
                update(v*2+1, tm+1, tr, pos, val);
            pull(v);
        }
    }

    int query(int v, int tl, int tr, int l, int r, int idx) {
        if (l > r)
            return idx;
        if (l == tl and r == tr)
            return t[v][idx];
        int tm = (tl + tr) / 2;
        return query(v*2+1, tm+1, tr, max(l, tm+1), r,
                     query(v*2, tl, tm, l, min(r, tm), idx));
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, Q; cin >> N >> Q;

    vector<array<int, 16>> a(N, array<int, 16>());

    vector op(16, vector<array<int,16>>(2));

    for (int k = 0; k < 16; k++) {
        for (int o = 0; o < 2; o++) {
            for (int x = 0; x < 16; x++) {
                int y;
                if (o == 0)
                    y = (x + k) % 16;
                else
                    y = x ^ k;
                op[k][o][x] = y;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        char t; cin >> t;
        int k; cin >> k;

        int o = 0;
        if (t == 'x')
            o = 1;
        a[i] = op[k][o];
    }

    segtree st(a, N);

    while (Q--) {
        int i, k; char t; cin >> i >> t >> k;
        int o = 0;
        if (t == 'x')
            o = 1;

        st.update(1, 0, N-1, i-1, op[k][o]);
        cout << st.query(1, 0, N-1, 0, N-1, 0) << endl;

        // for (int x = 0; x < 16; x++) {
        //     if (res.a0[x] != 0) {
        //         cout << x << endl;
        //         break;
        //     }
        // }
    }

    return 0;
}
