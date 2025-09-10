#include <iostream>
#include <string>

std::string ABC131A() {
    std::string s;
    std::cin >> s;
    for (int i = 0; i < 3; i++) {
        if (s[i] == s[i + 1]) {
            return "Bad";
        }
    }
    return "Good";
}

int main() {
    std::cout << ABC131A();
    return 0;
}