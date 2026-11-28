#include <bits/stdc++.h>

int dm = 0;
std::vector<int> digits;

int search(int d, std::vector<bool> mask) {
    int curr_d = 0;
    if (d == dm) {
        int sum = 0;
        for (int i = 0; i < d; i++) {
            if (mask[i]) {
                sum += digits[i];
                curr_d++;
            }
        }
        if (sum % 3 == 0 && curr_d > 0) {
            return curr_d;
        }
        return -1;
    }
    mask.push_back(false);
    int d_0 = search(d + 1, mask);
    mask[d] = true;
    int d_1 = search(d + 1, mask);
    return std::max(d_0, d_1);
}

int ABC182C() {
    long long n;
    std::cin >> n;
    while (n > 0) {
        int d = n % 10;
        n /= 10;
        digits.push_back(d);
        dm++;
    }
    std::vector<bool> mask;
    int ans = search(0, mask);
    if (ans == -1) return -1;
    else return dm - ans;
}   

int main() { 
    std::cout << ABC182C();
    return 0;
}