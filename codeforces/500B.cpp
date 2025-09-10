#include <bits/stdc++.h>

void problem500B() {
    // get input
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    std::vector<std::string> a(n);
    std::vector<std::vector<int>> adj_list(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '1') adj_list[i].push_back(j);
        }
    }

    // BFS across graph to get connected components vector "comp"
    std::vector<bool> seen(n);
    std::vector<std::vector<int>> comp;
    for (int start = 0; start < n; start++) {
        if (seen[start]) continue;
        seen[start] = true;
        std::queue<int> q;
        q.push(start);
        std::vector<int> c;
        c.push_back(p[start]);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v: adj_list[u]) {
                if (seen[v]) continue;
                seen[v] = true;
                q.push(v);  
                c.push_back(p[v]);
            }
        }
        comp.push_back(c);
    }

    // for each connected component, sort component and put back in vector p
    for (auto& c: comp) {
        std::set<int> c_set;  // for faster lookup
        for (int c_i: c) {
            c_set.insert(c_i);
        }
        std::sort(c.begin(), c.end());
        int ctr = 0;
        while (ctr < c.size()) {
            for (int i = 0; i < n; i++) { 
                if (c_set.count(p[i])) {
                    p[i] = c[ctr];
                    ctr++;
                }
            }
        }
    }

    // print result
    for (int p_i: p) {
        std::cout << p_i << " ";
    }
}

int main() {
    problem500B();
    return 0;
}