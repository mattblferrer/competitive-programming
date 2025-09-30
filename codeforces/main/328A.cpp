#include <bits/stdc++.h>

int problem328A() {
    std::array<int, 4> a;
    for (int i = 0; i < 4; i++) {
        std::cin >> a[i];
    }
    
    bool arith = true, geom = true;
    for (int i = 0; i < 2; i++) {
        if (a[i + 2] - a[i + 1] != a[i + 1] - a[i]) arith = false;
    }
    if (arith) return a[3] * 2 - a[2];
    for (int i = 0; i < 2; i++) {
        if (a[i + 2] * a[i] != a[i + 1] * a[i + 1]) geom = false;
    }
    if (geom) {
        if (a[0] == 0) return 42;
        if (a[1] == a[0]) return 42;
        if ((a[3] * a[3]) % a[2] != 0) return 42;
        return (a[3] * a[3] / a[2]);
    }
    return 42;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << problem328A() << "\n";
    return 0;
}