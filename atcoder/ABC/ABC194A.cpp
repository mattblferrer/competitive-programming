#include <bits/stdc++.h>

int ABC194A() {
    int a, b;
    std::cin >> a >> b;
    if ((a + b) >= 15 && b >= 8) return 1;
    if ((a + b) >= 10 && b >= 3) return 2;
    if ((a + b) >= 3) return 3;
    return 4;
}   

int main() { 
    std::cout << ABC194A();
    return 0;
}