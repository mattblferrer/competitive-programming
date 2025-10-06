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
    deque<int> top(n), bottom(n);
    for (int i = 0; i < n; i++) {
        top[i] = i + 1;
        bottom[i] = i + 1;
    }
    vector<char> tc(n + 1), bc(n + 1);
    for (int i = 0; i < k; i++) {
        if (s[i] == '0') {
            top.pop_front();
            bottom.pop_front();
        }
        else if (s[i] == '1') {
            top.pop_back();
            bottom.pop_back();
        }
        else {
            top.pop_front();
            bottom.pop_back();
        }
    }
    set<int> ts, bs;
    for (int i = 0; i < top.size(); i++) {
        ts.insert(top[i]);
        bs.insert(bottom[i]);
    }
    vector<char> ans(n + 1);
    int leftq = -1, rightq = -1;
    for (int i = 1; i <= n; i++) {
        if (ts.count(i) && bs.count(i)) ans[i] = '+';
        else if (ts.count(i) || bs.count(i)) {
            ans[i] = '?';
            if (leftq == -1) leftq = i;
            rightq = i;
        }
        else ans[i] = '-';
    }
    for (int i = 1; i <= n; i++) {
        if (leftq <= i && i <= rightq && ans[i] == '-') cout << '?';
        else cout << ans[i];
    }
    cout << "\n";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}