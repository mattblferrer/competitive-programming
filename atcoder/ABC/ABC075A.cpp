#include <bits/stdc++.h>

int ABC075A() {
    int a, b, c;
    std::cin >> a >> b >> c;
    return a ^ b ^ c;
}

int main() {
    std::cout << ABC075A();
    return 0;
}