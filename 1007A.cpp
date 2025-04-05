#include <algorithm>
#include <iostream>
#include <vector>

long long problem1007A() {
    long long n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    // TODO: solve
}

int main() {
    std::cout << problem1007A();
    return 0;
}