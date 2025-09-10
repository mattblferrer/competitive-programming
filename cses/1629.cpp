#include <algorithm>
#include <iostream>
#include <vector>

int CSES1629() {
    int n, a, b;
    std::cin >> n;
    std::vector<std::pair<int, int>> movies(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b;
        movies[i] = {a, b};
    }
    std::sort(movies.begin(), movies.end(), [](std::pair<int, int> a, 
        std::pair<int, int> b) {
            return a.second < b.second;
        });

    int watched = 1;
    int end = movies[0].second;
    for (int i = 1; i < n; i++) {
        if (movies[i].first >= end) {
            end = movies[i].second;
            watched++;
        }
    }

    return watched;
}

int main() {
    std::cout << CSES1629();
    return 0;
}