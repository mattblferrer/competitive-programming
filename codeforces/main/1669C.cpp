#include <iostream>
#include <string>

std::string problem1669C() {
    int n;
    std::cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < 2; i++) {
        for (int j = i; j < n - 2; j += 2) {
            if ((a[j] % 2) != (a[j + 2] % 2)) {
                return "NO";
            }
        }
    }
    return "YES";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1669C() << "\n";
    }
    
    return 0;
}