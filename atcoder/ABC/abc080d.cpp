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
    int* a = new int[200002];
    for (int i = 0; i < 200002; i++) {
        a[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        a[2*s[i] - 1]++;
        a[2*t[i]]--;
    }
    int max = 0;
    int sum = 0;
    for (int i = 0; i < 200002; i++) {
        sum += a[i];
        max = std::max(max, sum);
    }
    return std::min(max, ch);
}

int main() {
    std::cout << ABC080D();
    return 0;
}