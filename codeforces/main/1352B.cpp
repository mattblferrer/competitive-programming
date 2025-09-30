#include <bits/stdc++.h>

void problem1352B() {
    int n, k;
    std::cin >> n >> k;
    if (n % 2 == 0) {  // even n
        if (k % 2 == 0) {  // even k
            if (n < k) std::cout << "NO\n";
            else {
                std::cout << "YES\n";
                for (int i = 0; i < k - 1; i++) {
                    std::cout << "1 ";
                }
                std::cout << n - k + 1 << "\n";
            }
        }
        else {  // odd k
            if (n < 2*k) std::cout << "NO\n";
            else {
                std::cout << "YES\n";
                for (int i = 0; i < k - 1; i++) {
                    std::cout << "2 ";
                }
                std::cout << n - 2*k + 2 << "\n";
            }
        }
    }
    else {  // odd n, can only be represented with odd k
        if (k % 2 == 0) std::cout << "NO\n";
        else if (n < k) std::cout << "NO\n";
        else {
            std::cout << "YES\n";
            for (int i = 0; i < k - 1; i++) {
                std::cout << "1 ";
            }
            std::cout << n - k + 1 << "\n";
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1352B();
    }
    return 0;
}