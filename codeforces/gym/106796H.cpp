#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; std::cin >> n;
    std::vector<int> ans(n, -1), problems;
    for (int i = 0; i < n; i++) {
        int vala, valb;
        for (int j = 0; j < n; j++) {
            if (i != j) { std::cout << n << ' '; }
            else { std::cout << "1 "; }
        }
        std::cout << std::endl;
        std::cin >> vala; if (vala == 0) { return 0; }
        for (int j = 0; j < n; j++) {
            if (i != j) { std::cout << n << ' '; }
            else { std::cout << (2 * n) << ' '; }
        }
        std::cout << std::endl;
        std::cin >> valb; if (valb == 0) { return 0; }
        if (vala > valb) { ans[i] = vala + 1; }
        else if (vala < valb) { ans[i] = 2 * n - valb; }
        else { problems.push_back(i); }
    }

    for (auto i : problems) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (ans[j] == -1) { std::cout << n << ' '; }
                else { std::cout << ans[j] << ' '; }
            }
            else { std::cout << "1 "; }
        }
        std::cout << std::endl;
        int val; std::cin >> val; if (val == 0) { return 0; }
        ans[i] = val + 1;
    }

    for (auto i : ans) { std::cout << i << ' '; } std::cout << std::flush;
}