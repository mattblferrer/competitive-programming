#include <bits/stdc++.h>

int ABC070B() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    int cnt = 0;
    for (int i = 0; i < 100; i++) {
        if (a <= i && i < b && c <= i && i < d) cnt++; 
    }
    return cnt;
}

int main() {
    std::cout << ABC070B();
    return 0;
}