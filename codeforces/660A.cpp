#include <iostream>
#include <numeric>
#include <vector>

void problem660A() {
    int n;
    std::cin >> n;
    int k = 0;
    int* a = new int[n];
    std::vector<int> a_new;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        a_new.push_back(a[i]);
        if (std::gcd(a[i], a[i + 1]) != 1) {
            a_new.push_back(1);
            k++;
        }
    }
    a_new.push_back(a[n - 1]);

    std::cout << k << "\n";
    for (int i = 0; i < a_new.size(); i++) {
        std::cout << a_new[i] << " ";
    }
}

int main() {
    problem660A();
    return 0;
}