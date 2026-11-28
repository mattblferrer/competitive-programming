#include <bits/stdc++.h>

std::string ABC110B() {
    int N, M, X, Y, Z;
    std::cin >> N >> M >> X >> Y;
    std::vector<int> x(N), y(M);
    for (int i = 0; i < N; i++) {
        std::cin >> x[i];
    }
    for (int i = 0; i < M; i++) {
        std::cin >> y[i];
    }
    std::sort(x.begin(), x.end(), std::greater());
    std::sort(y.begin(), y.end());
    int max_x = x[0];
    int min_y = y[0];
    if (max_x > min_y) return "War";
    for (int Z = max_x + 1; Z <= min_y; Z++) {
        if (X < Z && Z <= Y) return "No War"; 
    }
    return "War";
}   

int main() {
    std::cout << ABC110B();
    return 0;
}