#include <iostream>
#include <vector> 

void problem978C() {
    long long n, m;
    std::cin >> n >> m;
    std::vector<long long> a(n);
    std::vector<long long> b(m + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        std::cin >> b[i];
    }
    long long f = 1; 
    long long k = 0;
    for (int i = 1; i <= m; i++) {
        k += b[i] - b[i - 1];
        while (k > a[f - 1]) {
            k -= a[f - 1];
            f++;
        }
        std::cout << f << " " << k << "\n";
    }
}

int main() {
    problem978C();
    return 0;
}