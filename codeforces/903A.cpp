#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    vector<int> valid(101);
    valid[3] = 1;
    valid[7] = 1;
    for (int i = 0; i < 101; i++) {
        if (i >= 3 && valid[i - 3]) valid[i] = 1;
        if (i >= 7 && valid[i - 7]) valid[i] = 1;
    }

    int t; std::cin >> t; while (t--) {
        int n;
        cin >> n;
        if (valid[n]) cout << "YES\n";
        else cout << "NO\n";
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}