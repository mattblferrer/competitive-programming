#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

struct KMP {
    vector<int> par;
    int n;
    string s, f;
    KMP(string &s, string &f) {
        this->n = s.size(); this->s = s; this->f = f;
        if (f.size() > s.size()) return;

        par.resize(max(n, 2), 0);
        par[0] = -1, par[1] = 0;
        int i = 2, j = 0;
        while (i <= f.size()) {
            if (f[i - 1] == f[j]) par[i++] = ++j;
            else if (j > 0) j = par[j];
            else par[i++] = 0;
        }
    }
    vector<int> run() {
        if (f.size() > s.size()) return {};

        int i = 0, j = 0; vector<int> ans;
        while (i + j < s.size()) {
            if (s[i + j] == f[j]) {
                if (++j == f.size()) {
                    ans.push_back(i);
                    i += j - par[j];
                    if (j > 0) j = par[j];
                }
            }
            else {
                i += j - par[j];
                if (j > 0) j = par[j];
            }
        }
        return ans;
    }
};

void solve() {
    string s, t;
    cin >> s >> t;
    ll n = s.size(), m = t.size();
    while (n + t.size() > s.size()) s += s;
    KMP kmp(s, t);
    vector<int> ind = kmp.run();
    ll ans = 0;
    for (ll i = 0; i < ind.size(); i++) {
        if (ind[i] >= n) break;
        ans++;
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}