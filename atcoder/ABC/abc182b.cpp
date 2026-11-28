#include <bits/stdc++.h>

int ABC182B() {
    int n, ans = 0, div = 0;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 2; i <= 1000; i++) {
        int curr = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] % i == 0) curr++;
        }
        if (curr > div) {
            div = curr;
            ans = i;
        }
    }
    return ans;
}   

int main() { 
    std::cout << ABC182B();
    return 0;
}