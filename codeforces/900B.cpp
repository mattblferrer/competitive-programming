#include <bits/stdc++.h>

int problem900B() {
    int a, b, c, rem = 0, pos = 0;
    std::cin >> a >> b >> c;
    for (int i = 0; i < b + 10; i++) {
        a *= 10;
        rem = a / b;
        a -= rem * b;
        pos++;
        if (rem == c) return pos;
    }
    return -1;
}

int main() {
    std::cout << problem900B();
    return 0;
}