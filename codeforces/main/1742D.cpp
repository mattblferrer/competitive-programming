#include <iostream>
#include <map>
#include <numeric>

int problem1742D() {
    int n, a_i;
    std::cin >> n;
    std::map<int, int> a;
    int max = -1;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a[a_i] = i;
    }
    for (const auto& pair_1: a) {
        for (const auto& pair_2: a) {
            if (std::gcd(pair_1.first, pair_2.first) == 1) {
                max = std::max(max, pair_1.second + pair_2.second + 2);
            }
        }
    }
    return max;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1742D() << "\n";
    }
    return 0;
}
