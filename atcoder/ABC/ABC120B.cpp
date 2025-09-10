#include <bits/stdc++.h>

int ABC120B() {
    int a, b, k, ctr = 0;
    std::cin >> a >> b >> k;
    for (int i = std::min(a, b); i > 0; i--) {
        if (a % i == 0 && b % i == 0) ctr++;
        if (ctr == k) return i;
    }
    return 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << ABC120B() << "\n";
    return 0;
}