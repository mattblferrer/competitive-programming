#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    vector<double> s(6);
    cin >> s[3] >> s[4] >> s[5];
    double ans = 0;
    for (int i = 3; i <= 5; i++) {
        double pol = (i * pow(s[i], 2)) / (4 * tan(M_PI / i));
        ans += pol * s[i] * sqrt(1 - 1 / (4 * pow(sin(M_PI / i), 2))) / 3;
    }
    cout << ans;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}