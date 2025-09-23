#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;
#define M_PI 3.14159265358979323846

char solve() {
    string x1, x2;
    int p1, p2;
    cin >> x1 >> p1 >> x2 >> p2;
    while (x1.size() < x2.size()) {
        x1 += '0';
        p1--;
    }
    while (x1.size() > x2.size()) {
        x2 += '0';
        p2--;
    }
    if (p1 < p2) return '<';
    if (p1 > p2) return '>';
    if (x1 < x2) return '<';
    if (x1 > x2) return '>';
    return '=';
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    int t; std::cin >> t; while (t--) cout << solve() << '\n';
    return 0;
}