#include <algorithm>
#include <iostream>
#include <vector>

int problem149A() {
    int k, a_i;
    std::cin >> k;
    std::vector<int> a;
    for (int i = 0; i < 12; i++) {
        std::cin >> a_i;
        a.push_back(a_i);
    }
    
    if (k == 0) {
        return 0;
    }
    std::sort(a.begin(), a.end(), std::greater());
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        sum += a[i];
        if (sum >= k) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    std::cout << problem149A();	

    return 0;
}