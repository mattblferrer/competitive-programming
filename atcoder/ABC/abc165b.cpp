#include <bits/stdc++.h>

long long ABC165B() {
    long long x, curr = 100, ctr = 0;
    std::cin >> x;
    while (curr < x) {
        curr += curr / 100;
        ctr++;
    }
    return ctr;
}

int main() {
    std::cout << ABC165B();
    return 0;
}