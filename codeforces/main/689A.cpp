#include <bits/stdc++.h>

std::string problem689A() {
    int n, left_w = 3, right_w = -1, up_h = 4, down_h = -1, sides = 0, mid = 0;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<int> w_map = {1, 0, 1, 2, 0, 1, 2, 0, 1, 2};
    std::vector<int> h_map = {3, 0, 0, 0, 1, 1, 1, 2, 2, 2}; 
    for (int i = 0; i < n; i++) {
        int d = s[i] - '0';
        int w = w_map[d];
        int h = h_map[d];
        left_w = std::min(left_w, w);
        right_w = std::max(right_w, w);
        up_h = std::min(up_h, h);
        down_h = std::max(down_h, h);
        if (w == 1) {
            mid = std::max(mid, h);
        }
        else {
            sides = std::max(sides, h);
        }
    }
    if (right_w != 2 && mid != 3) return "NO";
    if (left_w != 0 && mid != 3) return "NO";
    if (up_h != 0) return "NO";
    if (down_h != 3 && sides != 2) return "NO";
    return "YES";
}

int main() {
    std::cout << problem689A();	
    return 0;
}