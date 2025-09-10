#include <iostream>
#include <string>

std::string problem1857A() {
    long long n, a_i, sum_a;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        sum_a += a_i;
    }
    if (sum_a % 2 == 0) {
        return "YES";
    }
    else {
        return "NO";
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1857A() << std::endl;
    }

    return 0;
}