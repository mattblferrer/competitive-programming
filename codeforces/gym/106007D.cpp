#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> Adj;
typedef std::pair<int, int> Pair;

void solve() {
    int n; std::cin >> n;
    Adj beats(n);
    char c;
    for (int p1 = 0; p1 < n; p1++) {
        for (int p2 = 0; p2 < n; p2++) {
            std::cin >> c;
            if (c != '0') { // 1 or ?
                beats[p1].push_back(p2);
            }
        }
    }
    std::vector<bool> seen(n, false); seen[0] = true;
    std::vector<int> stack{0};
    std::vector<Pair> matches_rev;

    int cur, count = 0;
    while (!stack.empty()) {
        cur = stack.back(); stack.pop_back();
        count++;
        for (auto i : beats[cur]) {
            if (!seen[i]) {
                seen[i] = true;
                stack.push_back(i);
                matches_rev.push_back(Pair(cur, i));
            }
        }
    }

    if (count == n) {
        std::cout << "Yes\n";
        for (int i = matches_rev.size() - 1; i >= 0; i--) {
            std::cout << matches_rev[i].first + 1 << ' ' << matches_rev[i].second + 1 << '\n';
        }
    }
    else { std::cout << "No\n"; }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int q; std::cin >> q;
    while (q--) { solve(); }
}