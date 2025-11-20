#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, k;
    cin >> n >> k;
    map<ll, ll> a;
    for (ll i = 0; i < n; i++) {
        ll ai; 
        cin >> ai;
        a[ai] = i;
    }
    if (a.size() >= k) {
        cout << "YES\n";
        vector<ll> students;
        for (const auto& [ai, i]: a) {
            if (students.size() < k) students.push_back(i + 1);
        }
        sort(students.begin(), students.end());
        for (ll i = 0; i < k; i++) cout << students[i] << " ";
        cout << "\n";
        return;
    }
    cout << "NO\n";
    return;
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}