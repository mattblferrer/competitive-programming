#include <algorithm>
#include <iostream>
#include <vector>

long long ABC173D() {
    long long n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    long long comfort = 0;
    for (int i = 0; i < n - 1; i++) {
        comfort += a[n - (i + 1) / 2 - 1];
        
    }
    return comfort;
}   

int main() { 
    std::cout << ABC173D();
    return 0;
}