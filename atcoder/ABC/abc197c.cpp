#include <bits/stdc++.h>

int n, a_i;
std::vector<int> a;

int search(int d, std::vector<bool> mask) {
    if (d == n) {
        int p_or = 0, p_xor = 0, valid = 0;
        for (int i = 0; i < n; i++) {
            if (mask[i]) p_or = p_or | a[i];
            else {
                p_xor = p_xor ^ p_or; 
                p_or = a[i];
                valid = 1;
            }
        }
        if (valid) return p_xor ^ p_or;
        return pow(2, 31) - 1;
    }
    mask.push_back(false);
    int ans_0 = search(d + 1, mask);
    mask[d] = true;
    int ans_1 = search(d + 1, mask);
    return std::min(ans_0, ans_1);
}

int ABC197C() {
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a.push_back(a_i);
    }
    std::vector<bool> mask;
    return search(0, mask);
}   

int main() { 
    std::cout << ABC197C();
    return 0;
}