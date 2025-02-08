#include <iostream>

int ABC080D() {
    int n, ch;
    std::cin >> n >> ch;
    int* s = new int[n];
    int* t = new int[n];
    int* c = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> s[i] >> t[i] >> c[i];
    }
    // TODO: solve
    
}

int main() {
    std::cout << ABC080D();
    return 0;
}