#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n, m;
    cin >> n >> m;
    m *= 60;
    string s, e;
    for (int i = 0; i < n; i++) {
        cin >> s >> e;
        int sh = stoi(s.substr(0, 2));
        int sm = stoi(s.substr(3, 2));
        int eh = stoi(e.substr(0, 2));
        int em = stoi(e.substr(3, 2));
        int stime = sh * 60 + sm;
        int etime = eh * 60 + em;
        int diff = etime - stime;
        m -= diff;
    }
    if (m <= 0) cout << "YES\n";
    else cout << "NO\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}