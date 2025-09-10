#include <bits/stdc++.h>

void problem2131B() {
    int n;
    std::cin >> n;
    for (int i = 0; i < n / 2 - 1; i++) {
        std::cout << "-1 3 ";
    }
    if (n % 2 == 0) std::cout << "-1 2\n";
    else std::cout << "-1 3 -1\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2131B();
    }
    return 0;
}