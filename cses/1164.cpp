#include <algorithm>
#include <iostream>
#include <vector>

void CSES1164() {
    long long n, a, b;
    std::cin >> n;
    std::vector<std::pair<long long, long long>> customers(n);
    for (long long i = 0; i < n; i++) {
        std::cin >> a >> b;
        customers[i] = {a, b};
    }
    // TODO: solve
}

int main() {
    CSES1164();
    return 0;
}