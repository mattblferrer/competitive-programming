#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

struct city {
    int dist, idx, mini, maxi;
};

void solve() {
    int n, a_i;
    cin >> n;
    vector<city> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a_i;
        a[i] = {a_i, i, 0, 0};
    }
    sort(a.begin(), a.end(),[](city& x, city& y) {
        return x.dist < y.dist;
    });
    a[0].mini = a[1].dist - a[0].dist;
    a[0].maxi = a[n - 1].dist - a[0].dist;
    for (int i = 1; i < n - 1; i++) {
        a[i].mini = min(a[i].dist - a[i - 1].dist, a[i + 1].dist - a[i].dist);
        a[i].maxi = max(a[n - 1].dist - a[i].dist, a[i].dist - a[0].dist);
    }
    a[n - 1].mini = a[n - 1].dist - a[n - 2].dist;
    a[n - 1].maxi = a[n - 1].dist - a[0].dist;
    sort(a.begin(), a.end(),[](city& x, city& y) {
        return x.idx < y.idx;
    });
    for (int i = 0; i < n; i++) {
        cout << a[i].mini << " " << a[i].maxi << "\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}