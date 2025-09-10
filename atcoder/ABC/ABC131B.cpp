#include <iostream>

int ABC131B() {
    int n, l, sum, min_apple;
    std::cin >> n >> l;
    int min_diff = 999999999;
    for (int i = 1; i <= n; i++) {
        sum = -(l + i - 1);
        for (int j = 1; j <= n; j++) {
            sum += l + j - 1;
        }
        if (abs(sum - (sum + l + i - 1)) < min_diff) {
            min_apple = sum;
            min_diff = abs(sum - (sum + l + i - 1));
        }
    }
    return min_apple;
}

int main() {
    std::cout << ABC131B();
    return 0;
}