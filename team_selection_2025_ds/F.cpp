#include <bits/stdc++.h>

void problemF() {
    int n, p, d;
    std::string s;
    std::cin >> n >> p >> d >> s;
    std::vector<char> period(n * 2);
    for (int i = 0; i < n * 2; i++) {
        period[i] = s[i % n];
    }
    
    int cnt_w = 0, cnt_z = 0, ans = 0;
    for (int i = 0; i < p; i++) {
        if (period[i] == 'W') cnt_w++;
        else cnt_z++;
    }
    for (int i = p; i < n + p; i++) {
        if (cnt_z < d) ans++;
        if (period[i] == 'W') cnt_w++;
        else cnt_z++;
        if (period[i - p] == 'W') cnt_w--;
        else cnt_z--;
    }
    std::cout << ans;
}

int main() {
    problemF();
    return 0;
}