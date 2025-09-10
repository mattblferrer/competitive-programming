#include <bits/stdc++.h>

void CSES1645() {
    int n;
    std::cin >> n;
    std::vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::stack<int> s, pos;
    s.push(0);
    pos.push(0);
    for (int i = 1; i <= n; i++) {
        while (s.top() >= a[i]) {
            s.pop();
            pos.pop();
        }
        std::cout << pos.top() << " ";
        s.push(a[i]);
        pos.push(i);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES1645();
    return 0;
}