#include <iostream>
#include <string>
#include <vector>

int ABC381C() {
    int n, l, max_l, left, right;
    std::string s;
    std::cin >> n;
    std::cin >> s;
    std::vector<int> slashes;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '/') {
            slashes.push_back(i);
        }
    }

    max_l = 0;
    for (const auto& i: slashes) {
        left = i; 
        right = i;

        while (true) {
            if (left == 0 || right == n - 1) {
                break;
            }
            if (s[left - 1] != '1' || s[right + 1] != '2') {
                break;
            }
            left--;
            right++;
        }
        max_l = std::max(max_l, right - left + 1);
    }
    
    return max_l;
}

int main() { 
    std::cout << ABC381C();
    return 0;
}