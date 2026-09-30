#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    string t1, t2;
    cin >> t1 >> t2;
    int h1 = stoi(t1.substr(0, 2)), h2 = stoi(t2.substr(0, 2));
    int m1 = stoi(t1.substr(3, 2)), m2 = stoi(t2.substr(3, 2));
    int total_1 = h1 * 60 + m1, total_2 = h2 * 60 + m2;
    int mid = (total_1 + total_2) / 2;
    int h3 = mid / 60, m3 = mid % 60;

    if (h3 < 10) cout << "0";
    cout << h3 << ":";
    if (m3 < 10) cout << "0";
    cout << m3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}