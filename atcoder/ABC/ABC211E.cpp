#include <bits/stdc++.h>

int n, k; 
std::vector<std::string> s;
std::set<std::vector<std::string>> seen_states;

int search(int p) {
    int start_x = 0, start_y = 0, ans = 0;
    if (seen_states.count(s)) return 0;
    seen_states.insert(s);
    if (p == k) {
        return 1;
    }
    else if (p == 0) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (s[i][j] == '.') {
                    s[i][j] = '@';
                    ans += search(p + 1);
                    s[i][j] = '.';
                }
            }
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (s[i][j] == '@') {
                    start_x = i;
                    start_y = j;
                }
            }
        }
    }

    std::vector<std::vector<bool>> seen(n, std::vector<bool>(n));
    seen[start_x][start_y] = true;
    std::queue<std::pair<int, int>> q;
    q.push({start_x, start_y});

    while (!q.empty()) {
        std::pair<int, int> u = q.front();
        q.pop();
        int x = u.first;
        int y = u.second;
        if (x != 0 && !seen[x - 1][y]) {
            if (s[x - 1][y] == '@') {
                seen[x - 1][y] = true;
                q.push({x - 1, y});
            }
            else if (s[x - 1][y] == '.') {
                s[x - 1][y] = '@';
                ans += search(p + 1);
                s[x - 1][y] = '.';
            }
        }
        if (x != n - 1 && !seen[x + 1][y]) {
            if (s[x + 1][y] == '@') {
                seen[x + 1][y] = true;
                q.push({x + 1, y});
            }
            else if (s[x + 1][y] == '.') {
                s[x + 1][y] = '@';
                ans += search(p + 1);
                s[x + 1][y] = '.';
            }
        }
        if (y != 0 && !seen[x][y - 1]) {
            if (s[x][y - 1] == '@') {
                seen[x][y - 1] = true;
                q.push({x, y - 1});
            }
            else if (s[x][y - 1] == '.') {
                s[x][y - 1] = '@';
                ans += search(p + 1);
                s[x][y - 1] = '.';
            }
        }
        if (y != n - 1 && !seen[x][y + 1]) {
            if (s[x][y + 1] == '@') {
                seen[x][y + 1] = true;
                q.push({x, y + 1});
            }
            else if (s[x][y + 1] == '.') {
                s[x][y + 1] = '@';
                ans += search(p + 1);
                s[x][y + 1] = '.';
            }
        }
    }
    return ans;
}

int ABC211E() {
    std::cin >> n >> k;
    std::string s_i;
    for (int i = 0; i < n; i++) {
        std::cin >> s_i;
        s.push_back(s_i);
    }
    return search(0);
}   

int main() { 
    std::cout << ABC211E();
    return 0;
}