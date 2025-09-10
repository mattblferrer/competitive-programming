#include <iostream>
#include <string>
#include <vector>

std::string problem292B() {
    int n, m, a_i, b_i;
    std::cin >> n >> m;
    std::vector<int> neighbors(n);
    for (int i = 0; i < m; i++) {
        std::cin >> a_i >> b_i;
        neighbors[a_i - 1]++;
        neighbors[b_i - 1]++;
    }
    int ones = 0;
    int twos = 0;
    int centers = 0;
    for (int i: neighbors) {
        if (i == 1) ones++;
        if (i == 2) twos++;
        if (i == n - 1) centers++;
    }
    if (ones == 2 && twos == n - 2) return "bus topology";
    if (twos == n) return "ring topology";
    if (ones == n - 1 && centers == 1) return "star topology";
    return "unknown topology";
}

int main() {
    std::cout << problem292B();
    return 0;
}