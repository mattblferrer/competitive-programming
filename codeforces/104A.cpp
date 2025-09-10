#include <bits/stdc++.h>

int problem104A() {
    int n;
    std::cin >> n;
    if (n == 20) return 15;
    else if (11 <= n && n <= 19) return 4;
    else if (n == 21) return 4;
    else return 0;
}

int main() {
    std::cout << problem104A();	

    return 0;
}