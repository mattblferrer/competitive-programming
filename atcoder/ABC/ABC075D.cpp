#include <bits/stdc++.h>

long long ABC075D() {
    long long n, k, x_i, y_i;
    std::cin >> n >> k;
    std::vector<std::pair<long long, long long>> points(n);
    long long min_area = std::numeric_limits<long long>::max();
    for (int i = 0; i < n; i++) {
        std::cin >> x_i >> y_i;
        points[i] = {x_i, y_i};
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {  
            for (int l = 0; l < n; l++) {
                for (int m = 0; m < n; m++) {
                    int ct = 0;  // counter of number of points in rect
                    long long x_1 = std::min(points[i].first, points[j].first);
                    long long x_2 = std::max(points[i].first, points[j].first);
                    long long y_1 = std::min(points[l].second, points[m].second);
                    long long y_2 = std::max(points[l].second, points[m].second);
                    for (int o = 0; o < n; o++) {
                        long long x_o = points[o].first;
                        long long y_o = points[o].second;
                        if (x_1 <= x_o && x_o <= x_2 && y_1 <= y_o && y_o <= y_2) ct++;
                    }
                    long long area = (x_2 - x_1) * (y_2 - y_1);
                    if (ct >= k) min_area = std::min(min_area, area);
                }
                
            }     
        }
    }
    return min_area;
}

int main() {
    std::cout << ABC075D();
    return 0;
}