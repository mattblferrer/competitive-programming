#include <bits/stdc++.h>

long long CSES1071() {
    long long x, y;
    std::cin >> y >> x;
    long long loops = std::max(x, y) - 1;
    if (y < x) {
        if (loops % 2 == 0) return (loops + 1) * (loops + 1) - y + 1;
        else return loops * loops + y;
    }
    else {
        if (loops % 2 == 0) return loops * loops + x;
        else return (loops + 1) * (loops + 1) - x + 1;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << CSES1071() << "\n";
    }
    return 0;
}