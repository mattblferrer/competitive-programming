#include <iostream>

void ABC057B() {
    int n, m;
    std::cin >> n >> m;
    int* a = new int[n];
    int* b = new int[n];
    int* c = new int[m];
    int* d = new int[m];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> c[i] >> d[i];
    }
    
    int dist, min_i;
    for (int i = 0; i < n; i++) {
        int min_dist = 2000000000;
        for (int j = 0; j < m; j++) {
            dist = abs(c[j] - a[i]) + abs(d[j] - b[i]);
            if (min_dist > dist) {
                min_dist = dist;
                min_i = j;
            }
        }
        std::cout << min_i + 1 << "\n";
    }
}

int main() {
    ABC057B();
    return 0;
}