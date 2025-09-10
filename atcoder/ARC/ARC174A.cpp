#include <iostream>

long long ARC174A() {
    long long n, c;
    std::cin >> n >> c;
    long long* a = new long long[n];
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        sum += a[i];
    }

    long long k = 0;
    long long curr = 0;
    
    for (int i = 0; i < n; i++) {
        if (c > 0) {
            curr = std::max(0LL, curr + a[i]);
            k = std::max(curr, k);
        }
        else {
            curr = std::min(0LL, curr + a[i]);   
            k = std::min(curr, k);
        }   
    }
    return sum + k * (c - 1);
}

int main() {
    std::cout << ARC174A();
    return 0;
}