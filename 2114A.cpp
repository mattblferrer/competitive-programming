#include <bits/stdc++.h>

void problem2114A() {
    int s;
    std::cin >> s;
    for (int i = 0; i < 100; i++) {
        if (i * i == s) {
            std::cout << "0 " << i << "\n";
            return;
        }
    }
    std::cout << "-1\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2114A();
    }
    return 0;
}