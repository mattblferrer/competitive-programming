#include <iostream>
#include <string>

std::string ABC109A() {
    int a, b;
    std::cin >> a >> b;
    if ((a * b) % 2 == 0) {
        return "No";
    } 
    else {
        return "Yes";
    }
}

int main() {
    std::cout << ABC109A();
    return 0;
}