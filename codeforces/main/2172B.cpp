#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
using pld = pair<ld, ld>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

struct point {
    int si, ti;
    double end;
    bool type;
};

struct bus {
    int si, ti;
    double end;
};

void solve() {
    int n, m, l;
    double x, y;
    cin >> n >> m >> l >> x >> y;
    vector<bus> buses(n);
    for (int i = 0; i < n; i++) {
        int si, ti;
        cin >> si >> ti;
        buses[i] = {si, ti, 0};
    }
    vector<int> p(m);
    for (int i = 0; i < m; i++) cin >> p[i];

    vector<double> ans(m);
    for (int i = 0; i < n; i++) {
        buses[i].end = (buses[i].ti - buses[i].si) / x + (l - buses[i].ti) / y;
    }

    vector<point> pts(2 * n);
    for (int i = 0; i < n; i++) {
        pts[2 * i] = {buses[i].si, buses[i].ti, buses[i].end, true};
        pts[2 * i + 1] = {buses[i].si, buses[i].ti, buses[i].end, false};
    }

    vector<double> best(2 * n + 1);
    best[0] = l / y;
    set<pair<double, double>> inter;
    inter.insert({l / y, l / y});
    sort(pts.begin(), pts.end(), [](const point &a, const point &b) {
        return a.si < b.si;
        });
    vector<int> st(2 * n + 1);
    st[0] = -1;
    for (int i = 0; i < 2 * n; i++) st[i + 1] = pts[i].si;

    for (int i = 0; i < pts.size(); i++) {
        if (pts[i].type) inter.insert({pts[i].end, i});
        else inter.erase({pts[i].end, i});
        best[i + 1] = min((double)(l - pts[i].si) / y, (*(inter.begin())).first);
    }

    for (int i = 0; i < m; i++) {
        int low = distance(st.begin(), upper_bound(st.begin(), st.end(), p[i])) - 1;
        double take_bus = best[low];
        ans[i] = min((double)(l - p[i]) / y, take_bus);
    }
    for (int i = 0; i < m; i++) cout << ans[i] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(10);

    solve();
    return 0;
}