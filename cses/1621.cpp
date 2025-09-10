#include <bits/stdc++.h>

int CSES1621() {
    int n, x_i;
    std::cin >> n;
    std::set<int> x;
    for (int i = 0; i < n; i++) {
        std::cin >> x_i;
        x.insert(x_i);
    }
    return x.size();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << CSES1621() << "\n";
    return 0;
}