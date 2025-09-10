#include <bits/stdc++.h>

void problem2128B() {
    int n, p_i;
    std::cin >> n;
    std::deque<int> p;
    for (int i = 0; i < n; i++) {
        std::cin >> p_i;
        p.push_back(p_i);
    }
    std::vector<char> ans(n);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            if (p.front() < p.back()) {
                p.pop_back();
                ans[i] = 'R';
            }
            else {
                p.pop_front();
                ans[i] = 'L';
            }
        }
        else {
            if (p.front() > p.back()) {
                p.pop_back();
                ans[i] = 'R';
            }
            else {
                p.pop_front();
                ans[i] = 'L';
            }
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << ans[i];
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        problem2128B();
    }
    return 0;
}