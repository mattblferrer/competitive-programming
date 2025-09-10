#include <bits/stdc++.h>

std::string ABC165A() {
    int k, a, b;
    std::cin >> k >> a >> b;
    for (int i = a; i <= b; i++) {
        if (i % k == 0) return "OK";
    }
    return "NG";
}

int main() {
    std::cout << ABC165A();
    return 0;
}