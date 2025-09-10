#include <iostream>
#include <string>

int problem1791C() {
    int n, ctr;
    ctr = 0;
    std::string s; 
    std::cin >> n >> s;
    for (int i = 0; i < (s.length() + 1) / 2; i++) {
        if (s[i] != s[s.length() - i - 1]) {
            ctr++;
        }
        else {
            break;
        }
    }
    return s.length() - 2*ctr;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1791C() << std::endl;
    }

    return 0;
}