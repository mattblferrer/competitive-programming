#include <iostream>
#include <string>

std::string ABC079A() {
    std::string n;
    std::cin >> n;
    for (int i = 0; i < 2; i++) {
        if (n[i] == n[i + 1] && n[i + 1] == n[i + 2]) {
            return "Yes";
        }
    }
    return "No";
}

int main() {
    std::cout << ABC079A();
    return 0;
}