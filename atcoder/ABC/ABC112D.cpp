#include <iostream>

int ABC112D() {
    int n, m;
    std::cin >> n >> m;
    for (int i = n; i <= m; i++) {
        if (m % i == 0) {
            return m / i;
        }
    }
    return 0;
}

int main() {
    std::cout << ABC112D();
    return 0;
}