#include <iostream>
#include <string>

std::string problem1862C() {
    int n;
    std::cin >> n;
    int* a = new int[n];  // vertical
    int* b = new int[n];  // horizontal
    int curr_h = 0;
    bool valid = true;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] > n) {
            valid = false;
        }
    }
    if (!valid) {
        return "NO";
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = curr_h; j < a[i]; j++) {
            b[j] = i + 1;
        }
        curr_h = a[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return "NO";
        }
    }
    return "YES";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1862C() << "\n";
    }
    return 0;
}