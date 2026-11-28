#include <iostream>
#include <string>

int ABC382A() {
    int n, d;
    std::string s;
    std::cin >> n >> d >> s;
    int empty = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '.') {
            empty++;
        }
    }
    return empty + d;
}

int main() { 
    std::cout << ABC382A();
    return 0;
}