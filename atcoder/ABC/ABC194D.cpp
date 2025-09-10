#include <bits/stdc++.h>

double ABC194D() {
    double n;
    std::cin >> n;
    double ans = 0;
    for (int i = 1; i < n; i++) {
        ans += n / (n - i);
    }
    return ans;
}   

int main() { 
    std::cout << ABC194D();
    return 0;
}