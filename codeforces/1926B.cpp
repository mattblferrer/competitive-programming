#include <iostream>
#include <string>

std::string problem1926B() {
    int n;
    std::cin >> n;
    std::string line, result;
    int prev = 0;

    for (int i = 0; i < n; i++) {
        std::cin >> line;
        int ctr = 0;
        for (int j = 0; j < n; j++) {
            if (line[j] == '1') {
                ctr++;
            }
        }
        if (ctr && prev) {
            if (ctr == prev) { // square
                result = "SQUARE";
            }
            else {  // triangle
                result = "TRIANGLE";
            }
        }
        prev = ctr;
    }

    return result;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1926B() << "\n";
    }
    
    return 0;
}