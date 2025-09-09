#include <bits/stdc++.h>

std::string problem2120A() {
    int l_1, b_1, l_2, b_2, l_3, b_3;
    std::cin >> l_1 >> b_1 >> l_2 >> b_2 >> l_3 >> b_3;
    // stack vertically
    if (l_1 == l_2 && l_2 == l_3 && b_1 + b_2 + b_3 == l_1) return "YES";

    // arrange horizontally
    if (b_1 == b_2 && b_2 == b_3 && l_1 + l_2 + l_3 == b_1) return "YES";

    // two smaller rectangles on side of biggest rectangle
    if (b_1 - l_1 == l_2 && l_2 == l_3 && b_2 + b_3 == b_1) return "YES";

    // two smaller rectangles below biggest rectangle
    if (l_1 - b_1 == b_2 && b_2 == b_3 && l_2 + l_3 == l_1) return "YES";

    return "NO";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2120A() << "\n";
    }
    return 0;
}