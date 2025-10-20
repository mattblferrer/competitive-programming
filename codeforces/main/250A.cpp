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
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int neg = 0, cnt = 0;
    vector<int> indices;
    for (int i = 0; i < n; i++) {
        cnt++;
        if (a[i] < 0) neg++;
        if (neg == 3) {
            indices.push_back(cnt - 1);
            cnt = 1;
            neg = 1;
        }
    }
    indices.push_back(cnt);
    cout << indices.size() << "\n";
    for (int i: indices) cout << i << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}