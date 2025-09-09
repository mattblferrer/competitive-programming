#include <bits/stdc++.h>

void problem1118C() {
    int n;
    std::cin >> n;
    std::vector<int> a(n * n);
    std::map<int, int> count;
    for (int i = 0; i < n * n; i++) {
        std::cin >> a[i];
        count[a[i]]++;
    }

    // TODO: solve
}

int main() {
    problem1118C();
    return 0;
}