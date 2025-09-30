#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void problem632C() {
    int n;
    std::cin >> n;
    std::string a_i;
    std::vector<std::string> a;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a.push_back(a_i);
    }

    std::sort(a.begin(), a.end(), [](std::string x, std::string y) {
        return x + y < y + x;
    });
    std::string concat;
    for (const auto& a_i: a) {
        concat += a_i;
    }
    std::cout << concat;
}

int main() {
    problem632C();
    return 0;
}