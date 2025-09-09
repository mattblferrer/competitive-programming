#include <iostream>

bool solve(int n, int m) {
    if (n == m) {
        return true;
    }
    if (n < m) {
        return false;
    }
    if (n % 3 != 0) {
        return false;
    }
    return solve(2 * n / 3, m) || solve(n / 3, m);
}

void problem1829D() {
    int n, m;
    std::cin >> n >> m;
    if (solve(n, m)) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1829D();
    }
    
    return 0;
}