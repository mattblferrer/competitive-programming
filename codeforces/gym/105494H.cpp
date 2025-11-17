#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

vector<ll> parent;
vector<ll> sz;

void make_set(ll a) {
    parent[a] = a;
    sz[a] = 1;
}

ll find_set(ll a) {
    if (parent[a] == a) return a;
    return parent[a] = find_set(parent[a]);
}

bool union_sets(ll a, ll b) {
    a = find_set(a);
    b = find_set(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

bool is_connected(ll a, ll b) {
    return find_set(a) == find_set(b);
}

void solve() {
    ll n;
    cin >> n;
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) {
        cin >> b[i];
        b[i]--;
    }

    parent.resize(n);
    sz.resize(n);
    for (ll i = 0; i < n; i++) make_set(i);
    for (ll i = 0; i < n; i++) {
        if (b[i] == -1) continue;
        union_sets(i, b[i]);
    }
    map<ll, ll> ceos;
    for (ll i = 0; i < n; i++) {
        ceos[find_set(i)]++;
    }
    ll maxsize = 0, maxceo = 0;
    for (const auto& [ceo, cnt]: ceos) {
        if (maxsize < cnt) {
            maxsize = cnt;
            maxceo = ceo;
        }
    }
    while (b[maxceo] != -1) maxceo = b[maxceo];
    cout << maxceo + 1 << " " << maxsize;  // 1-index
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}