#include <algorithm>
#include <iostream>
#include <vector>

std::string problem1008B() {
    int n, w_i, h_i;
    std::cin >> n;
    std::vector<std::pair<int, int>> rect(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w_i >> h_i;
        rect[i] = {w_i, h_i};
    }
    // get maximum starting height of rect[0]
    rect[0] = {std::min(rect[0].first, rect[0].second), std::max(rect[0].first, rect[0].second)};
    
    for (int i = 1; i < n; i++) {
        if (rect[i - 1].second < rect[i].second) { 
            if (rect[i - 1].second < rect[i].first) {
                return "NO";
            }
            rect[i] = {rect[i].second, rect[i].first};
            continue;
        }
        if (rect[i - 1].second >= rect[i].first) {
            rect[i] = {std::min(rect[i].first, rect[i].second), std::max(rect[i].first, rect[i].second)};
        }
    }
    return "YES";
}

int main() {
    std::cout << problem1008B();
    return 0;
}