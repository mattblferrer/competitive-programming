#include <bits/stdc++.h>

void problem6C() {
    int n;
    std::cin >> n;
    std::vector<int> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
    }
    int a_ptr = 0, b_ptr = n - 1, a_bars = 0, b_bars = 0;
    while (a_ptr <= b_ptr) {
        if (a_bars <= b_bars) {
            a_bars += t[a_ptr];
            a_ptr++;
        }
        else {
            b_bars += t[b_ptr];
            b_ptr--;
        }
    }
    std::cout << a_ptr << " " << n - b_ptr - 1;
}

int main() {
    problem6C();
    return 0;
}