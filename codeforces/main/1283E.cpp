#include <bits/stdc++.h>

void problem1283E() {
    int n;
    std::cin >> n;
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    std::sort(x.begin(), x.end());
    std::set<int> minset, maxset;
    std::vector<bool> min_c(n + 1), max_c(n + 1);
    for (int i = 0; i < n; i++) {
        // minimum houses, merge houses
        if (min_c[x[i] - 1]) {
            minset.insert(x[i] - 1);
        }
        else if (min_c[x[i]]) {
            minset.insert(x[i]);
        }
        else if (min_c[x[i] + 1]) {
            minset.insert(x[i] + 1);
        }
        else {
            minset.insert(x[i] + 1);
            min_c[x[i] + 1] = true;
        }

        // maximum houses, split houses if space available
        if (!max_c[x[i] - 1]) {
            maxset.insert(x[i] - 1);
            max_c[x[i] - 1] = true;
        }
        else if (!max_c[x[i]]) {
            maxset.insert(x[i]);
            max_c[x[i]] = true;
        }
        else if (!max_c[x[i] + 1]) {
            maxset.insert(x[i] + 1);
            max_c[x[i] + 1] = true;
        }
    }
    std::cout << minset.size() << " " << maxset.size();
}

int main() {
    problem1283E();
    return 0;
}