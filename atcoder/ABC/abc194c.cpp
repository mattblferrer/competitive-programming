#include <bits/stdc++.h>

long long ABC194C() {
    int n, a_i;
    std::cin >> n;
    std::map<int, int> a_cnt;
    for (int i = 0; i < n; i++) {
        std::cin >> a_i;
        a_cnt[a_i]++;
    }
    long long sq = 0;
    for (int i = -200; i <= 200; i++) {
        for (int j = -200; j <= 200; j++) {
            sq += pow(abs(i - j), 2) * a_cnt[i] * a_cnt[j]; 
        }
    }
    return sq / 2;
}   

int main() { 
    std::cout << ABC194C();
    return 0;
}