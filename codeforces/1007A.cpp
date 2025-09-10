#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

long long problem1007A() {
    long long n;
    std::cin >> n;
    std::vector<long long> a(n);
    std::map<long long, long long> count;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        count[a[i]]++;
    }
    long long max = 0;
    for (const auto& pair: count) {
        max = std::max(max, pair.second);
    }
    return n - max;
}

int main() {
    std::cout << problem1007A();
    return 0;
}