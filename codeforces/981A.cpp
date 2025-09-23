#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            string check = s.substr(i, j - i);
            bool valid = false;
            for (int k = 0; k < check.size(); k++) {
                if (check[k] != check[check.size() - k - 1]) valid = true;
            }
            if (valid) ans = max(ans, (int)(check.size()));
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