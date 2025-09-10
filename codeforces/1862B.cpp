#include <iostream>
#include <vector>

void problem1862B() {
    int n;
    std::cin >> n;
    int* b = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    std::vector<int> a;
    for (int i = 0; i < n - 1; i++) {
        a.push_back(b[i]);
        if (b[i + 1] < b[i]) {
            a.push_back(b[i + 1]);
        }
    }
    a.push_back(b[n - 1]);
    
    std::cout << a.size() << "\n";
    for (const auto& a_i: a) {
        std::cout << a_i << " ";
    }
    std::cout << "\n";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem1862B();
    }
    return 0;
}