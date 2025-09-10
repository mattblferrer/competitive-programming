#include <iostream>
#include <string>

std::string ABC080B() {
    std::string n;
    std::cin >> n;
    int sum = 0;
    for (int i = 0; i < n.size(); i++) {
        sum += n[i] - '0';
    }
    if (std::stoi(n) % sum == 0) {
        return "Yes";
    } 
    else {
        return "No";
    }
}

int main() {
    std::cout << ABC080B();
    return 0;
}