#include <iostream>
#include <vector>

int ABC116C() {
    int n;
    std::cin >> n;
    std::vector<int> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    int water = h[0];
    for (int i = 0; i < n - 1; i++) {
        if (h[i] < h[i + 1]) {
            water += h[i + 1] - h[i];   
        }
    }
    return water;
}

int main() {
    std::cout << ABC116C();
    return 0;
}