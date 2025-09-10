#include <bits/stdc++.h>

std::vector<std::string> graycode(int n) {
    if (n == 1) {
        return {"0", "1"};
    }
    std::vector<std::string> prev = graycode(n - 1);
    int x = prev.size();
    std::vector<std::string> ans(x * 2);
    for (int i = 0; i < x; i++) {
        ans[i] = "0" + prev[i];
    }
    for (int i = 0; i < x; i++) {
        ans[x + i] = "1" + prev[x - i - 1];
    }
    return ans;
}

void CSES2205() {
    int n;
    std::cin >> n;
    for (std::string s: graycode(n)) {
        std::cout << s << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    CSES2205();
    return 0;
}