#include <bits/stdc++.h>

double ABC211A() {
    double a, b;
    std::cin >> a >> b;
    return (a - b) / 3 + b;
}

int main() { 
    std::cout << ABC211A();
    return 0;
}