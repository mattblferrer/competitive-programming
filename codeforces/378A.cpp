#include <bits/stdc++.h>

void problem378A() {
    int a, b, w_1 = 0, d = 0, w_2 = 0;
    std::cin >> a >> b;
    for (int i = 1; i <= 6; i++) {
        if (abs(a - i) < abs(b - i)) w_1++;
        else if (abs(a - i) == abs(b - i)) d++;
        else w_2++;
    }
    std::cout << w_1 << " " << d << " " << w_2;
}

int main() {
    problem378A();
    return 0;
}