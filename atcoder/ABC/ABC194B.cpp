#include <bits/stdc++.h>

int ABC194B() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    int min = 9999999;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
        min = std::min(min, a[i] + b[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            min = std::min(min, std::max(a[i], b[j]));
        }
    }
    return min;
}   

int main() { 
    std::cout << ABC194B();
    return 0;
}