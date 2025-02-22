#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

void problem22D() {
    int n, a, b;
    std::cin >> n;
    std::vector<std::pair<int, int>> segments;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b;
        segments.push_back({std::min(a, b), std::max(a, b)});
    }
    // TODO: solve
}

int main() {
    problem22D();
    return 0;
}