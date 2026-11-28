#include <iostream>

int ABC103C() {
    int n, max_f;
    std::cin >> n;
    int* a = new int[n];
    
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    max_f = 0;
    for (int i = 0; i < n; i++) {
        max_f += a[i] - 1;
    }
    return max_f;
}

int main() { 
    std::cout << ABC103C();
    return 0;
}