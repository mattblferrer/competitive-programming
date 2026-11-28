#include <bits/stdc++.h>

int ABC120A() {
    int a, b, c;
    std::cin >> a >> b >> c;
    return std::min(b / a, c);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC120A() << "\n";
    return 0;
}