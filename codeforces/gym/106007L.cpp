#include <iostream>
#include <vector>
#include <bitset>

static const int BIT = 31;

/*
10110
00100
01110
11110
11100
01100
XX X

11010
11011
11110
11111

3
10 3
3 3 3 3 3 3 3 3 3 1
3
2 4 6
10 3
1 1 1 1 1 1 1 1 1 3
3
2 4 6
10 3
1 1 1 1 1 1 1 1 1 1
3
2 4 6
*/

void solve() {
    int n, window, allor = 0, alland = 0xFFFFFFFF; std::cin >> n >> window;
    std::vector<int> arr(n); for (auto &i : arr) { std::cin >> i; allor |= i; alland &= i; }

    bool zero = (allor == alland);
    int needs = allor ^ alland;

    // std::cerr << needs << '\n';

    std::vector<bool> problem(n, false);
    for (int i = 0; i < n; i++) {
        if (arr[i] != allor) { problem[i] = true; }
    }

    int ind = 0, purecount = 0;
    while (ind < n) {
        if (problem[ind]) { purecount++; ind += window; }
        else { ind++; }
    }


    int q, val; std::cin >> q;
    while (q--) {
        std::cin >> val;
        if (zero) { std::cout << "0\n"; continue; }
        bool possible = true, total = false;

        for (int i = 0; i < BIT; i++) {
            if (((needs >> i) & 1) && !(val & 1)) { possible = false; break; } // if necessary bit is missing, impossible
            if ((1 - (allor >> i) & 1) && (val & 1)) { total = true; } // if null bit is present, total
            val >>= 1;
        }

        if (possible) {
            if (total) { std::cout << (n - 1) / window + 1 << '\n'; }
            else { std::cout << purecount << '\n'; }
        }
        else { std::cout << "-1\n"; }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int q; std::cin >> q;
    while (q--) { solve(); }
}