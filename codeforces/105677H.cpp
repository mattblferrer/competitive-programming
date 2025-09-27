#include <bits/stdc++.h>
using ll = long long;
using ld = long double;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846
const long long INF = 2e18;
const long long MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    map<string, int> names;
    string name;
    for (int i = 0; i < n; i++) {
        cin >> name;
        names[name]++;
    }
    string ans = "";
    int cnt = 0;
    for (const auto& pair: names) {
        if (pair.second > cnt) {
            cnt = pair.second;
            ans = pair.first;
        }
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