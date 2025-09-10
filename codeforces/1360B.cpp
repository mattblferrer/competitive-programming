#include <algorithm>
#include <iostream>
#include <vector>

int problem1360B() {
    int n, s_i, min_diff;
    min_diff = 1000000;
    std::vector<int> s;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> s_i;
        s.push_back(s_i);
    }

    std::sort(s.begin(), s.end());
    for (int i = 0; i < n - 1; i++) {
        min_diff = std::min(min_diff, s[i + 1] - s[i]);
    }
    return min_diff;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1360B() << std::endl;
    }

    return 0;
}