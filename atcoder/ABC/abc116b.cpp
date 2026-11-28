#include <iostream>

int ABC116B() {
    int s;
    std::cin >> s;
    int steps = 1;
    while (s != 4 && s != 2 && s != 1) {
        if (s % 2 == 0) s = s / 2;
        else s = 3*s + 1;
        steps++;
    }
    return steps + 3;
}

int main() {
    std::cout << ABC116B();
    return 0;
}