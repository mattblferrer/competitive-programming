#include <bits/stdc++.h>

int n, l, r, x, c_i; 
std::vector<int> c;

long long ways(int ctr, std::vector<bool> choose) {
    if (ctr == n) {
        int max = 0;
        int min = 9999999;
        int sum = 0;
        int prob = 0;
        for (int i = 0; i < n; i++) {
            if (choose[i]) {
                max = std::max(max, c[i]);
                min = std::min(min, c[i]);
                sum += c[i];
                prob++;
            }
        }
        if (prob < 2) return 0;
        if (sum > r || sum < l) return 0;
        if ((max - min) < x) return 0;
        return 1;
    }
    choose.push_back(false);
    long long w_0 = ways(ctr + 1, choose);
    choose[ctr] = true;
    long long w_1 = ways(ctr + 1, choose);
    return w_0 + w_1;
}

long long problem550B() {
    std::cin >> n >> l >> r >> x;
    for (int i = 0; i < n; i++) {
        std::cin >> c_i;
        c.push_back(c_i);
    }
    std::vector<bool> choose;
    return ways(0, choose);
}

int main() {
    std::cout << problem550B();
    return 0;
}