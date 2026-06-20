#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

int par[400001];
void buildKMP(vector<int>& f) {
    par[0] = -1, par[1] = 0;
    int i = 2, j = 0;
    while (i <= f.size()) {
        if (f[i - 1] == f[j]) par[i++] = ++j;
        else if (j > 0) j = par[j];
        else par[i++] = 0;
    }
}
std::vector<int> KMP(vector<int>& s, vector<int>& f) {
    buildKMP(f); // call once if f is the same 
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

string solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> a_diff(2 * n - 1), b_diff(n - 1);
    for (int i = 0; i < 2 * n - 1; i++) {
        a_diff[i] = (a[(i + 1) % n] - a[i % n] + 360000) % 360000;
    }
    for (int i = 0; i < n - 1; i++) {
        b_diff[i] = b[i + 1] - b[i];
    }
    vector<int> matches = KMP(a_diff, b_diff);
    if (matches.size() > 0) return "possible";
    return "impossible";
}

int main() {
    cout << solve() << "\n";

    return 0;
}