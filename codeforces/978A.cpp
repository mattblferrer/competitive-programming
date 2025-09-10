#include <iostream>
#include <vector> 

void problem978A() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> new_a;
    std::vector<bool> seen(1001);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        if (seen[a[i]]) continue;
        seen[a[i]] = true;
        new_a.push_back(a[i]);
    }
    std::cout << new_a.size() << "\n";
    for (int i = new_a.size() - 1; i >= 0; i--) {
        std::cout << new_a[i] << " ";
    }
}

int main() {
    problem978A();
    return 0;
}