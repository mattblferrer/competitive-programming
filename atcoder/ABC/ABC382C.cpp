#include <iostream> 

void ABC382C() {
    int n, m;
    std::cin >> n >> m;
    int* a = new int[n];
    int* b = new int[m];
    int* a_min = new int[n];
    int am = 1000000;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a_min[i] = std::min(am, a[i]);
        am = a_min[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }

    for (int i = 0; i < m; i++) {
        int left = -1;
        int right = n;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            if (b[i] < a_min[mid]) {
                left = mid;
            }
            else {
                right = mid;
            }       
        }
        if (right + 1 > n) {
            std::cout << -1 << std::endl;
        }
        else {
            std::cout << right + 1 << std::endl;   
        }
    }
}

int main() { 
    ABC382C();
    return 0;
}