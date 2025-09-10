#include <bits/stdc++.h>

void problem248B() {
    int n;
    std::cin >> n;
    std::array<int, 4> low = {-1, -1, -1, 210};
    std::array<std::string, 6> cycle = {"050", "080", "170", "020", "200", "110"};
    if (n < 4) {
        std::cout << low[n];
    }
    else {
        std::cout << '1';
        for (int i = 0; i < n - 4; i++) std::cout << '0';
        std::cout << cycle[(n - 4) % 6];
    }
}

int main() {
    problem248B();
    return 0;
}