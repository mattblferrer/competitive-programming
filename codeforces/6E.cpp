#include <bits/stdc++.h>

void problem6E() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> h[i];
    }
    std::multiset<int> books;
    int a = 0, l = 1;
    for (int r = 1; r <= n; r++) {  // find a
        books.insert(h[r]);
        int low = *books.begin();
        int high = *books.rbegin();
        if (high - low <= k) a = std::max(a, (int)books.size());
        else {
            while (high - low > k) {
                books.extract(h[l]);
                low = *books.begin();
                high = *books.rbegin();
                l++;
            }
        }
    }
    books.clear();
    for (int i = 1; i <= a; i++) {  // start sliding window
        books.insert(h[i]);
    }
    std::vector<int> start;
    for (int i = a + 1; i <= n + 1; i++) {  // find b
        int low = *books.begin();
        int high = *books.rbegin();
        if (high - low <= k) start.push_back(i - a);
        if (i == n + 1) break;
        books.insert(h[i]);
        books.extract(h[i - a]);
    }
    std::cout << a << " " << start.size() << "\n";
    for (int s: start) {
        std::cout << s << " " << s + a - 1 << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    problem6E();
    return 0;
}