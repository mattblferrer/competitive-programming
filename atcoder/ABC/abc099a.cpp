#include <iostream>
#include <string>

std::string ABC099A() {
    int n;
    std::cin >> n;
    if (n < 1000) {
        return "ABC";
    } 
    else {
        return "ABD";
    }
}

int main() { 
    std::cout << ABC099A();
    return 0;
}