#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

std::vector<long long> parent;
std::vector<long long> sz;

void make_set(long long a) {
    parent[a] = a;
    sz[a] = 1;
}

long long find_set(long long a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(long long a, long long b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) std::swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

bool is_connected(long long a, long long b) {
    return find_set(a) == find_set(b);
}

void solve() {
    int n;
    cin >> n;
    parent.resize(n + 1);
    sz.resize(n + 1);   
    for (int i = 0; i <= n; i++) make_set(i);
    vector<pll> oldr, newr;
    int oldp = -1;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        bool cycle = !union_sets(a, b);
        if (cycle) {
            oldr.push_back({a, b});
            oldp = find_set(a);
        }
    }
    if (oldp == -1) {
        cout << "0\n";
        return;
    }
    int newu = -1, newv = -1;
    set<int> seen;
    for (int i = 1; i <= n; i++) {
        int newp = find_set(i);
        if (newp != oldp && seen.count(newp) == 0) {
            newr.push_back({oldp, i});
            seen.insert(newp);
        }
    }
    cout << oldr.size() << "\n";
    for (int i = 0; i < oldr.size(); i++) {
        cout << oldr[i].first << " " << oldr[i].second << " ";
        cout << newr[i].first << " " << newr[i].second << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}