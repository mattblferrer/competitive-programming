#include <algorithm>
#include <iostream>
#include <vector>

void problem205A() {
    int n, a_i;
    std::cin >> n;
    std::vector<int> a;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a.push_back(a_i);
    }

    int min = *std::min_element(a.begin(), a.end());
    int count = std::count(a.begin(), a.end(), min);
    if (count > 1) {
        std::cout << "Still Rozdil";
    }
    else {
        for (int i = 0; i < n; i++) {
            if (a[i] == min) {
                std::cout << i + 1;
                break;
            }
        }
    }
}

int main() {
    problem205A();
    return 0;
}