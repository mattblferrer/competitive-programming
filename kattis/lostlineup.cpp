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
    map<int, int> m;
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
        m[a[i]] = i;
    }
    cout << "1 ";
    for (int i = 0; i < n - 1; i++) {
        cout << m[i] + 2 << " ";
    }
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);
    
    solve();
    return 0;
}