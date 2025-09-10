#include <bits/stdc++.h>

int problem9B() {
    int n, v_b, v_s, x_u, y_u;
    std::cin >> n >> v_b >> v_s;
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    std::cin >> x_u >> y_u;
    std::vector<double> time(n);
    for (int i = 0; i < n; i++) {
        time[i] += ((double)x[i] / v_b) + sqrt(pow(x_u - x[i], 2) + pow(y_u, 2)) / v_s;
    }
    double min_time = 999999999, min_idx = 1;
    for (int i = 1; i < n; i++) {
        if (time[i] <= min_time) {
            min_time = time[i];
            min_idx = i;
        }
    }
    return min_idx + 1;
}

int main() {
    std::cout << problem9B();
    return 0;
}