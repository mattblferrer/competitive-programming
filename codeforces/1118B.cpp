#include <bits/stdc++.h>

int problem1118B() {
    int n, good = 0, sum = 0, even = 0, odd = 0;
    std::cin >> n;
    std::vector<int> a(n + 5), left(n + 5), right(n + 5);
    for (int i = 2; i < n + 2; i++) {
        std::cin >> a[i];
        if (i % 2 == 0) {
            even += a[i];
            left[i] = even;
        }
        else {
            odd += a[i];
            left[i] = odd;
        }
    }
    for (int i = 2; i < n + 2; i++) {
        if (i % 2 == 0) {
            right[i] = even;
            even -= a[i];
        }
        else {
            right[i] = odd;
            odd -= a[i];
        }
    }
    for (int i = 2; i < n + 2; i++) { 
        if (left[i - 2] + right[i + 1] == left[i - 1] + right[i + 2]) {
            good++;
        }
    }
    return good;
}

int main() {
    std::cout << problem1118B() << '\n';
    return 0;
}