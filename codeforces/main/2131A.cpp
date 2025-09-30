#include <bits/stdc++.h>

int problem2131A() {
    int n;
    std::cin >> n;
    int ans = 1;
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    for (int i = 0; i < 100; i++) {
        bool step1 = false;
        for (int j = 0; j < n; j++) {
            if (a[j] > b[j]) {
                a[j]--;
                ans++;
                step1 = true;
                break;
            }
        }
        for (int j = 0; j < n; j++) {
            if (a[j] < b[j]) {
                a[j]++;
                break;
            }
        }
        if (!step1) break;
    }
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem2131A() << "\n";
    }
    return 0;
}