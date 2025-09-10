#include <iostream>

void ABC112A() {
    int n;
    std::cin >> n;
    if (n == 1) {
        std::cout << "Hello World";
    }
    else {
        int a, b;
        std::cin >> a >> b;
        std::cout << a + b;
    }
}

int main() {
    ABC112A();
    return 0;
}