#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;
struct point_segtree {
    int n;
    ll *vals;
    point_segtree(vector<ll> &ar, int n) {
        this->n = n;
        vals = new ll[2 * n];
        for (int i = 0; i < n; ++i) vals[i + n] = ar[i];
        for (int i = n - 1; i > 0; --i) vals[i] = vals[i << 1] + vals[i << 1 | 1];
    }
    void update(int i, ll v) {
        for (vals[i += n] += v; i > 1; i >>= 1)
            vals[i >> 1] = vals[i] + vals[i ^ 1];
    }
    ll query(int l, int r) {
        ll res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += vals[l++];
            if (r & 1) res += vals[--r];
        }
        return res;
    }
};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> column_stats(m, 0);
    vector<vector<int>> grid(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < s.size(); j++)
        {
            grid[i][j] = s[j] - '0';
            column_stats[j] += grid[i][j];
        }
    }

    if (m == 1)
    {
        for (int i = 0; i < q; i++)
        {
            int l, r; cin >> l >> r;
            cout << "Yes\n";
        }
        return;
    }

    vector<ll> segfeed(m - 1);
    for (int i = 0; i < m - 1; i++)
    {
        if (column_stats[i] <= column_stats[i + 1]) segfeed[i] = 1;
        else segfeed[i] = 0;
    }

    point_segtree segtree(segfeed, m - 1);
    for (int i = 0; i < q; i++)
    {
        int r, c;
        cin >> r >> c;
        r--; c--;

        if (grid[r][c] == 1)
        {
            grid[r][c] = 0;
            column_stats[c]--;
        }
        else
        {
            grid[r][c] = 1;
            column_stats[c]++;
        }

        if (c < m - 1)
        {
            int old_val = segtree.query(c, c);
            int upd_val = (column_stats[c] <= column_stats[c + 1]) ? 1 : 0;
            segtree.update(c, upd_val - old_val);
        }
        if (c > 0)
        {
            int old_val = segtree.query(c - 1, c - 1);
            int upd_val = (column_stats[c - 1] <= column_stats[c]) ? 1 : 0;
            segtree.update(c - 1, upd_val - old_val);
        }

        if (segtree.query(0, m - 2) == m - 1) cout << "Yes";
        else cout << "No";

        cout << "\n";
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}