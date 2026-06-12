#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    map<char, vector<int>> ind;
    for (int i = n - 1; i >= 0; i--) ind[s[i]].push_back(i);
    for (int i = 0; i < k; i++) {
        bool stop = false;
        for (char c = 'a'; c <= 'z'; c++) {
            if (!ind[c].empty()) {
                ind[c].pop_back();
                stop = true;
            }
            if (stop) break;
        }
    }
    string ans = "";
    vector<pair<int, char>> final_ind;
    for (char c = 'a'; c <= 'z'; c++) {
        for (int i = 0; i < ind[c].size(); i++) {
            final_ind.push_back({ind[c][i], c});
        }
    }
    sort(final_ind.begin(), final_ind.end());
    for (int i = 0; i < final_ind.size(); i++) {
        ans += final_ind[i].second;
    }
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}