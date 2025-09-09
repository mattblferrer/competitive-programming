#include <bits/stdc++.h>

std::string problem900A() {
    int n, pos = 0, neg = 0;
    std::cin >> n;
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
        if (x[i] > 0) pos++;
        else neg++;
    }
    if (pos <= 1 || neg <= 1) return "Yes";
    return "No";
}

int main() {
    std::cout << problem900A();
    return 0;
}