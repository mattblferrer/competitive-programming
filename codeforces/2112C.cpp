#include <bits/stdc++.h>

long long problem2112C() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int left = -1, right = i;
            while (right - left > 1) {
                int mid = (left + right) / 2;
                if (a[i] + a[j] + a[mid] > std::max(2 * a[j], a[n - 1])) {
                    right = mid;
                }
                else {
                    left = mid;
                }
            }
            ans += i - right;
        }
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2112C() << "\n";
    }
    return 0;
}