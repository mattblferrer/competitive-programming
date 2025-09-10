#include <bits/stdc++.h>

void problem550C() {
    std::string n;
    std::cin >> n;
    for (int i = 0; i < n.size(); i++) {  // 3-digit
        for (int j = i + 1; j < n.size(); j++) {
            for (int k = j + 1; k < n.size(); k++) {
                int x = 100 * (n[i] - '0') + 10 * (n[j] - '0') + (n[k] - '0');
                if (x % 8 == 0) {
                    std::cout << "YES\n" << x;
                    return; 
                }
            }
        }
    }
    for (int i = 0; i < n.size(); i++) {  // 2-digit
        for (int j = i + 1; j < n.size(); j++) {
            int y = 10 * (n[i] - '0') + (n[j] - '0');
            if (y % 8 == 0) {
                std::cout << "YES\n" << y;
                return; 
            }
        }
    }
    for (int i = 0; i < n.size(); i++) {  // 1-digit
        int z = n[i] - '0';
        if (z % 8 == 0) {
            std::cout << "YES\n" << z;
            return; 
        }
    }
    std::cout << "NO\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem550C();
    return 0;
}