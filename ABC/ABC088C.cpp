#include <bits/stdc++.h>

std::string ABC088C() {
    std::array<std::array<int, 3>, 3> c;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cin >> c[i][j];
        }
    }
    for (int a_1 = 0; a_1 <= 100; a_1++) {
        bool is_valid = true;
        int b_1 = c[0][0] - a_1;
        int b_2 = c[0][1] - a_1;
        int b_3 = c[0][2] - a_1;

        for (int i = 1; i <= 2; i++) {
            if (!(c[i][0] - b_1 == c[i][1] - b_2 && c[i][1] - b_2 == c[i][2] - b_3)) is_valid = false;
        }
        if (is_valid) return "Yes";
    }
    return "No";
}

int main() {
    std::cout << ABC088C();
    return 0;
}