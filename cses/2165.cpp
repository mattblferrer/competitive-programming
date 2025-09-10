#include <bits/stdc++.h>

void move(int n, int s, int m, int e) {
    if (n == 0) return;
    move(n - 1, s, e, m);
    std::cout << s << " " << e << "\n";
    move(n - 1, m, s, e);
}

void CSES2165() {
    int n;
    std::cin >> n;
    std::cout << pow(2, n) - 1 << "\n";
    move(n, 1, 2, 3);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES2165();
    return 0;
}