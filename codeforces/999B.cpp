#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

void solve() {
    int n;
    string s;
    cin >> n >> s;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) reverse(s.begin(), s.begin() + i);
    }
    cout << s;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}