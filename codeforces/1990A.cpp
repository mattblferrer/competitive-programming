#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string problem1990A() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        if (std::count(a.begin(), a.end(), a[i]) % 2 == 1) {
            return "YES";
        }
    }
    return "NO";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1990A() << "\n";
    }
    return 0;
}