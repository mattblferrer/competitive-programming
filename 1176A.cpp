#include <iostream>

long long problem1176A() {
    long long n, moves;
    std::cin >> n;
    moves = 0;

    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        }
        else if (n % 3 == 0) {
            n = 2 * n / 3;
        }
        else if (n % 5 == 0) {
            n = 4 * n / 5;
        }
        else {
            return -1;
        }
        moves++;
    }
    return moves;
}

int main() {
    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++) {
        std::cout << problem1176A() << "\n";	
    }   
   

    return 0;
}