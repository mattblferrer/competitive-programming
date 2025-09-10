#include <iostream>

void problem2094B() {
    int n, m, l, r, lp, rp;
    std::cin >> n >> m >> l >> r;
    lp = l;
    rp = r - (n - m);
    if (rp < 0) {
        lp -= rp;
        rp = 0;
    }
    std::cout << lp << " " << rp << "\n";
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2094B();
    }
    return 0;
}