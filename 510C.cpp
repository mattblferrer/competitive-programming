#include <bits/stdc++.h>

void dfs(std::vector<std::vector<int>>& adj_list, std::vector<bool>& seen, 
    std::vector<int>& stack, std::vector<bool>& curr, bool& cycle, int u) {
    if (seen[u]) return;
    if (curr[u]) {
        cycle = true;
        return;
    }
    curr[u] = true;
    for (int v: adj_list[u]) {
        dfs(adj_list, seen, stack, curr, cycle, v);
    }
    seen[u] = true;
    stack.push_back(u);
}

void problem510C() {
    int n;
    std::cin >> n;
    std::vector<std::string> name(n);
    for (int i = 0; i < n; i++) {
        std::cin >> name[i];
    }
    for (int i = 0; i < n - 1; i++) {
        if (name[i].substr(0, name[i + 1].length()) == name[i + 1]) {
            std::cout << "Impossible";
            return;
        }
    }
    std::vector<std::vector<int>> adj_list(26);
    std::vector<bool> seen(26);
    std::vector<int> stack;
    bool cycle = false;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < std::min(name[i].length(), name[i + 1].length()); j++) {
            if (name[i][j] == name[i + 1][j]) continue;
            adj_list[name[i + 1][j] - 97].push_back(name[i][j] - 97);
            break;
        }
    }
    for (int i = 0; i < 26; i++) {
        std::vector<bool> curr(26);
        dfs(adj_list, seen, stack, curr, cycle, i);
        if (cycle) {
            std::cout << "Impossible";
            return;
        }
    }
    for (int i = 0; i < 26; i++) {
        std::cout << (char)(stack[i] + 97);
    }
}

int main() {
    problem510C();
    return 0;
}