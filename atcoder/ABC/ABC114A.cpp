#include <iostream>
#include <string>

std::string ABC114A() {
    int x;
    int ages[3] = {3, 5, 7};
    std::cin >> x;
    for (int i = 0; i < 3; i++) {
        if (x == ages[i]) {
            return "YES";
        }
    }
    return "NO";
}

int main() {
    std::cout << ABC114A();
}