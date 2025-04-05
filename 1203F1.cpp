#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <queue>

std::string problem1203F1() {
    int n, r, a_i, b_i;
    std::cin >> n >> r;
    std::vector<std::pair<int, int>> pos;
    std::vector<std::pair<int, int>> neg;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i >> b_i;
        if (b_i >= 0) {
            pos.push_back({a_i, b_i});
        }
        else {
            neg.push_back({a_i, b_i});
        }
    }

    std::sort(pos.begin(), pos.end(), [](std::pair<int, int> a,
        std::pair<int, int> b) {
            return a.first < b.first;
        });
    for (const auto& p: pos) {
        if (r < p.first) {
            return "NO";
        }
        r += p.second;
    }
    std::sort(neg.begin(), neg.end(), [](std::pair<int, int> a,
        std::pair<int, int> b) {
            return b.first - a.second < a.first - b.second;
        });
    for (const auto& p: neg) {
        if (r < p.first) {
            return "NO";
        }
        r += p.second;
    }
    if (r < 0) {
        return "NO";
    }
    return "YES";
}

int main() {
    std::cout << problem1203F1();
    return 0;
}