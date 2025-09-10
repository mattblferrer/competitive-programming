#include <iostream>

void problem2039A() {
    int n;
    std::cin >> n;

    for (int i = 1; i <= n; i++) {
        std::cout << i * 2 - 1 << " ";
    }
    std::cout << "\n";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2039A();	
    }
    
    return 0;
}