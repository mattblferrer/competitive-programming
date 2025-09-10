#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

void problem105562H() {
    int n, x, y;
    std::cin >> n;
    std::cout << "? " << n << " 1\n" << std::flush;
    std::cin >> x;
    if (x == n) {
        std::cout << "! " << n << " 1\n" << std::flush;
        return;
    }
    std::cout << "? " << n - x << " 1\n" << std::flush;
    std::cin >> y;
    std::cout << "! " << x << " " << y << "\n" << std::flush;
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem105562H();
    return 0;
}