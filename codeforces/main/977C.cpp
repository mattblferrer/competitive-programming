#include <algorithm> 
#include <iostream>
#include <map>

long long problem977C() {
    long long n, k, a_i;
    std::cin >> n >> k;
    std::map<long long, long long> count;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        count[a_i]++;
    }
    long long c = 0;
    if (k == 0) {
        if (count[1] == 0) {
            return 1;
        }
        return -1;
    }
    for (const auto& pair: count) {
        c += pair.second;
        if (c == k) {
            return pair.first; 
        }
        if (c > k) {
            return -1;
        }
    }
    return -1;
}

int main() {
    std::cout << problem977C();
    return 0;
}