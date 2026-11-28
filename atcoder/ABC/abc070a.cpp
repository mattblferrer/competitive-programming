#include <bits/stdc++.h>

std::string ABC070A() {
    std::string n;
    std::cin >> n;
    if (n[0] == n[2]) return "Yes";
    else return "No";
}

int main() {
    std::cout << ABC070A();
    return 0;
}