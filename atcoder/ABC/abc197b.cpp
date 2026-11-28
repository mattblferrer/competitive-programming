#include <bits/stdc++.h>

int ABC197B() {
    int h, w, x, y, ans = 1;
    std::cin >> h >> w >> x >> y;
    std::vector<std::string> s(h);
    for (int i = 0; i < h; i++) {
        std::cin >> s[i];
    }
    for (int i = x - 2; i >= 0; i--) {
        if (s[i][y - 1] == '#') break;
        ans++;
    }
    for (int i = x; i < h; i++) {
        if (s[i][y - 1] == '#') break;
        ans++;
    }
    for (int i = y - 2; i >= 0; i--) {
        if (s[x - 1][i] == '#') break;
        ans++;
    }
    for (int i = y; i < w; i++) {
        if (s[x - 1][i] == '#') break;
        ans++;
    }
    return ans;
}   

int main() { 
    std::cout << ABC197B();
    return 0;
}