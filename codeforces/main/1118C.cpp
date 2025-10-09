#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n * n);
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n * n; i++) cin >> a[i];
    map<int, int> cnt;
    for (int i = 0; i < n * n; i++) {
        cnt[a[i]]++;
    }
    priority_queue<pair<int, int>> pq;
    for (const auto& pair: cnt) pq.push({pair.second, pair.first});
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n / 2; j++) {
            auto pair = pq.top();
            int val = pair.first, key = pair.second;
            pq.pop();
            if (val < 4) {
                cout << "NO\n";
                return;
            }
            ans[i][j] = ans[i][n - j - 1] = ans[n - i - 1][j] = ans[n - i - 1][n - j - 1] = key;
            pq.push({val - 4, key});
        }
    }
    if (n % 2 != 0) {
        for (int i = 0; i < n / 2; i++) {
            auto pair = pq.top();
            int val = pair.first, key = pair.second;
            pq.pop();
            if (val < 2) {
                cout << "NO\n";
                return;
            }
            ans[i][n / 2] = ans[n - i - 1][n / 2] = key;
            pq.push({val - 2, key});
        }
        for (int i = 0; i < n / 2; i++) {
            auto pair = pq.top();
            int val = pair.first, key = pair.second;
            pq.pop();
            if (val < 2) {
                cout << "NO\n";
                return;
            }
            ans[n / 2][i] = ans[n / 2][n - i - 1] = key;
            pq.push({val - 2, key});
        }
        auto pair = pq.top();
        int val = pair.first, key = pair.second;
        pq.pop();
        if (val != 1) {
            cout << "NO\n";
            return;
        }
        ans[n / 2][n / 2] = key;
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << ans[i][j] << " ";
        cout << "\n";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}