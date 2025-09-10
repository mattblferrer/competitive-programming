#include <algorithm>
#include <iostream>
#include <vector>

int problem609A() {
    int n, m, a_i;
    std::cin >> n >> m;
    std::vector<int> a;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a.push_back(a_i);
    }
    std::sort(a.begin(), a.end(), std::greater<int>());
    for (int i = 0; i < n; i++) {
        if (m <= 0) {
            return i;
        }
        m -= a[i];
    }
    return n;
}

int main() {
    std::cout << problem609A();
    return 0;
}