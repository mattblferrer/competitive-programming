#include <bits/stdc++.h>

int ABC118A() {
    int a, b;
    std::cin >> a >> b;
    if (b % a == 0) return a + b;
    else return b - a;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC118A() << "\n";
    return 0;
}