#include <iostream>

int problem1999B() {
    int* a = new int[2];
    int* b = new int[2];
    std::cin >> a[0] >> a[1] >> b[0] >> b[1];
    int ways = 0;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int t_1 = 0;
            int t_2 = 0;
            if (a[i] > b[j]) {
                t_1 = 1;
            }
            else if (a[i] < b[j]) {
                t_1 = -1;
            }
            if (a[1 - i] > b[1 - j]) {
                t_2 = 1;
            }
            else if (a[1 - i] < b[1 - j]) {
                t_2 = -1;
            }
            if (t_1 + t_2 > 0) {
                ways++;
            }
        }
    }
    return ways;
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        std::cout << problem1999B() << "\n";	
    }

    return 0;
}