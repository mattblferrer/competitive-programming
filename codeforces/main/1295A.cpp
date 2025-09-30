#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    int n;
    cin >> n;
    if (n % 2 == 0) {
        for (int i = 0; i < n / 2; i++) cout << "1";
    }
    else {
        cout << "7";
        for (int i = 0; i < n / 2 - 1; i++) cout << "1";
    }
    cout << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}