#include <iostream>
#include <string>

int problem2093B() {
    std::string n;
    std::cin >> n;
    char min_digit = '9';
    int min_pos;
    int digits = 0;
    for (int i = 0; i < n.size(); i++) {
        if (n[i] != '0') {
            min_digit = n[i];
            min_pos = i;
        }
    }
    for (int i = 0; i < min_pos; i++) {
        if (n[i] != '0') digits++;
    }
    for (int i = min_pos + 1; i < n.size(); i++) {
        digits++;
    }
    return digits;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2093B() << "\n";
    }
    return 0;
}