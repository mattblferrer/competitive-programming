#include <bits/stdc++.h>

std::string ABC054A() {
    int a, b;
    std::cin >> a >> b;
    if (a == 1 && b == 1) return "Draw";
    if (a == 1) return "Alice";
    if (b == 1) return "Bob";
    if (a > b) return "Alice";
    if (b > a) return "Bob";
    return "Draw";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC054A() << "\n";
    return 0;
}