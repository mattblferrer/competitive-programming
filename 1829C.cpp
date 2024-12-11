#include <iostream>
#include <string>

int problem1850C() {
    int n, m_i;
    std::cin >> n;
    std::string skills;
    std::string available = "00";
    int min_0 = 200001;
    int min_1 = 200001;
    int min_01 = 400001;

    for (int i = 0; i < n; i++) {
        std::cin >> m_i >> skills;
        if (skills[0] == '1' && skills[1] == '1') {
            min_01 = std::min(min_01, m_i);
            available[0] = available[1] = '1';
        }
        else if (skills[0] == '1') {
            min_0 = std::min(min_0, m_i);
            available[0] = '1';
        }
        else if (skills[1] == '1') {
            min_1 = std::min(min_1, m_i);
            available[1] = '1';
        }
    }
    if (available == "11") {
        return std::min(min_0 + min_1, min_01);
    }
    return -1;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1850C() << std::endl;
    }

    return 0;
}