#include <bits/stdc++.h>

long long problem18C() {
    long long n, l = 0, r = 0, ans = 0;
    std::cin >> n;
    std::vector<long long> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
        r += s[i];
    }
    for (int i = 0; i < n - 1; i++) {
        l += s[i];
        r -= s[i];
        if (l == r) ans++;
    }
    return ans;
}

int main() {
    std::cout << problem18C();
    return 0;
}