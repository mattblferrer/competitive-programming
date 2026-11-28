#include <bits/stdc++.h>

std::string ABC088A() {
    int n, a;
    std::cin >> n >> a;
    if (n % 500 > a) return "No";
    return "Yes";
}

int main() {
    std::cout << ABC088A();
    return 0;
}