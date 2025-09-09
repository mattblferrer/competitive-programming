#include <iostream>
#include <string>

std::string problem1097A() {
    std::string table;
    std::cin >> table;
    std::string* cards = new std::string[5];

    for (int i = 0; i < 5; i++) {
        std::cin >> cards[i];
        char rank = cards[i][0];
        char suit = cards[i][1];

        if ((rank == table[0]) || (suit == table[1])) {
            return "YES";
        }
    }
    return "NO";
}

int main() {
    std::cout << problem1097A() << std::endl;

    return 0;
}