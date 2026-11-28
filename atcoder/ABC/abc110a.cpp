#include <bits/stdc++.h>

int ABC110A() {
    int a, b, c;
    std::cin >> a >> b >> c;
    return std::max({10*a + b + c, a + 10*b + c, a + b + 10*c});
}

int main() {
    std::cout << ABC110A();
    return 0;
}