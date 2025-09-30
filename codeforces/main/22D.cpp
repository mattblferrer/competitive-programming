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
    std::vector<int> coords;  // coordinates of nails
    std::sort(segments.begin(), segments.end(), [](std::pair<int, int> a, 
        std::pair<int, int> b) {
            return a.second < b.second;
        });
    for (int i = 0; i < n; i++) {
        if (coords.empty() || !(segments[i].first <= coords.back() 
            && coords.back() <= segments[i].second)) {
                coords.push_back(segments[i].second);
        }
    }
    std::cout << coords.size() << "\n";
    for (int c: coords) {
        std::cout << c << " ";
    }
}

int main() {
    problem22D();
    return 0;
}