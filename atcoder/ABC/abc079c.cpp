#include <iostream>
#include <string>

bool checkEquation(std::string equation) {
    int terms[4];
    for (int i = 0; i < 7; i += 2) {
        terms[i / 2] = stoi(equation.substr(i, 1));
    }
    int total = terms[0];
    for (int i = 1; i < 4; i++) {
        if (equation[2 * i - 1] == '+') {
            total += terms[i];
        }
        else {
            total -= terms[i];
        }
    }
    return total == 7;
}

std::string ABC079C() {
    std::string equation;
    equation.resize(9);
    equation[7] = '=';
    equation[8] = '7';
    char operations[2] = {'+', '-'};
    std::string digits;
    std::cin >> digits;
    for (int i = 0; i < 8; i += 2) {
        equation[i] = digits[i / 2];
    }
    for (int i = 0; i < 2; i++) {
        equation[1] = operations[i];
        for (int j = 0; j < 2; j++) {
            equation[3] = operations[j];
            for (int k = 0; k < 2; k++) {
                equation[5] = operations[k];
                if (checkEquation(equation)) return equation;
            }
        }
    }
    return equation;
}

int main() {
    std::cout << ABC079C();
    return 0;
}