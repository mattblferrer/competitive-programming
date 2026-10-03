#include <iostream>
#include <vector>

int main() {
    int n, m; std::cin >> n >> m;
    std::vector<int> arr(n), maxes;
    bool possible = true;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
        if (arr[i] > (m / 2)) { maxes.push_back(i); }
        if ((arr[i] > ((m + 1) / 2))) { possible = false; }
    }

    if (!possible) { std::cout << "-1"; return 0; }

    std::vector<std::vector<bool>> grid(n, std::vector<bool>(m, false));

    if (!(m & 1)) { // easy even case
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                grid[i][j] = ((j & 1) == (i & 1)) && ((j / 2) < arr[i]);
            }
        }
    }

    else { // odd case

        if (maxes.empty()) { // easy odd case
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    grid[i][j] = ((j & 1) == (i & 1)) && ((j / 2) < arr[i]);
                }
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    std::cout << grid[i][j];
                }
                std::cout << '\n';
            }
            return 0;
        }

        // hard odd case
        // prelude
        int last = maxes[0], cur = 0;

        while (cur < last) {
            for (int j = 0; j < m; j++) {
                grid[cur][j] = ((j & 1) == (last - cur & 1)) && ((j / 2) < arr[cur]);
            }
            cur++;
        }

        for (int i = 1; i < maxes.size(); i++) {
            // start on max row
            for (int j = 0; j < m; j++) {
                grid[cur][j] = !(j & 1);
            }
            cur++;

            if ((maxes[i] - last) & 1) { // hard subcase
                int head = 0;
                while (cur < maxes[i]) {
                    head += m - 2 * arr[cur];
                    if (head > (m + 1)) { head = m + ((maxes[i] & 1) == (cur & 1) ? 0 : 1); }
                    for (int j = 0; j < m; j++) {
                        grid[cur][(j + head) % m] = !(j & 1) && ((j / 2) < arr[cur]);
                    }
                    cur++;
                }

                if (head < m) { possible = false; break; }
            }
            else { // easy subcase
                while (cur < maxes[i]) {
                    for (int j = 0; j < m; j++) {
                        grid[cur][j] = ((j & 1) == (cur - last & 1)) && ((j / 2) < arr[cur]);
                    }
                    cur++;
                }
            }

            last = maxes[i];
        }

        // coda
        while (cur < n) {
            for (int j = 0; j < m; j++) {
                grid[cur][j] = ((j & 1) == (cur - last & 1)) && ((j / 2) < arr[cur]);
            }
            cur++;
        }

        if (!possible) { std::cout << "-1"; return 0; }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
}