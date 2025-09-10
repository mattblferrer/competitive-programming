#include <bits/stdc++.h>

void CSES1076() {
    int n, k, med;
    std::cin >> n >> k;
    std::vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> x[i];
    }
    std::multiset<int> low, high;  // sliding window <= median, > median
    low.insert(x[1]);
    for (int i = 2; i <= k; i++) {
        med = *low.rbegin();
        if (x[i] < med) low.insert(x[i]);
        else high.insert(x[i]);
        if (high.size() > k / 2) {
            int move = *high.begin();
            high.extract(move);
            low.insert(move); 
        }
        else if (low.size() > (k + 1) / 2) {
            int move = *low.rbegin();
            low.extract(move);
            high.insert(move);
        }
    }
    for (int i = k + 1; i <= n + 1; i++) {
        med = *low.rbegin();
        std::cout << med << " ";
        if (i == n + 1) break;
        if (x[i] <= med) low.insert(x[i]);
        else high.insert(x[i]);
        if (x[i - k] <= med) low.extract(x[i - k]);
        else high.extract(x[i - k]);
        if (high.size() > k / 2) {
            int move = *high.begin();
            high.extract(move);
            low.insert(move); 
        }
        else if (low.size() > (k + 1) / 2) {
            int move = *low.rbegin();
            low.extract(move);
            high.insert(move);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES1076();
    return 0;
}