#include <bits/stdc++.h>

std::string problem2123A() {
    int n;
    std::cin >> n;
    if (n <= 2) return "Alice";
    if (n % 4 == 0) return "Bob";
    else return "Alice";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2123A() << "\n";
    }
    return 0;
}