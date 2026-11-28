#include <bits/stdc++.h>

int n, a, b, c, l_i;
std::vector<int> l;
int search(int curr, int x, int y, int z) {
    if (curr == n) {
        if (std::min({x, y, z}) <= 0) return 10000000;
        return abs(a - x) + abs(b - y) + abs(c - z) - 30;
    }
    return std::min({
        search(curr + 1, x, y, z),
        search(curr + 1, x + l[curr], y, z) + 10, 
        search(curr + 1, x, y + l[curr], z) + 10,
        search(curr + 1, x, y, z + l[curr]) + 10
    });
}

int ABC119C() {
    std::cin >> n >> a >> b >> c;
    for (int i = 0; i < n; i++) {
        std::cin >> l_i;
        l.push_back(l_i);
    }
    return search(0, 0, 0, 0);
}

int main() {
    std::cout << ABC119C();
    return 0;
}
