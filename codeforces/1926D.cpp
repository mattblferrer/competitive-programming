#include <iostream>
#include <map>

int problem1926D() {
    int n;
    std::cin >> n;
    int groups = 0;
    int a_i;
    std::map<int, int> g;

    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        g[a_i]++;
    }
    for (const auto& pair: g) {
        if (g.count(~pair.first + (1 << 31)) > 0) {
            groups += std::max(pair.second, g[~pair.first + (1 << 31)]);
        }
        else {
            groups += 2 * pair.second;
        }
    }

    return groups / 2;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1926D() << "\n";
    }
    
    return 0;
}