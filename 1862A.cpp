#include <iostream>
#include <string>

std::string problem1862A() {
    int n, m;
    std::cin >> n >> m;
    std::string* str = new std::string[n];
    for (int i = 0; i < n; i++) {
        std::cin >> str[i];
    }

    int pos = 0;
    std::string comp = "vika ";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (str[j][i] == comp[pos]) {
                pos++;
                break;
            }
        }
    }
    if (pos == 4) {
        return "YES";
    }
    return "NO";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1862A() << "\n";
    }
    return 0;
}