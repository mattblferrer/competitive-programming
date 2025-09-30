#include <bits/stdc++.h>

std::string problem2112A() {
    int a, x, y;
    std::cin >> a >> x >> y;
    for (int b = -100; b < 200; b++) {
        if (a == b) continue;
        if (abs(b - x) < abs(a - x) && abs(b - y) < abs(a - y)) return "YES";
    }
    return "NO";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2112A() << "\n";
    }
    return 0;
}