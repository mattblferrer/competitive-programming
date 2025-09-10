#include <iostream>
#include <vector>

int ABC166B() {
    int n, k, d_i, a_i;
    std::cin >> n >> k;
    std::vector<bool> snacks(n);
    for (int i = 0; i < k; i++) {
        std::cin >> d_i;
        for (int j = 0; j < d_i; j++) {
            std::cin >> a_i;
            snacks[a_i - 1] = true;
        } 
    }
    int count = 0;
    for (bool s: snacks) {
        if (!s) count++;
    }
    return count;
}

int main() {
    std::cout << ABC166B();
    return 0;
}