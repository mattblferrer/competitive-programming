#include <iostream>
#include <string>

std::string ABC089B() {
    int n;
    char s_i;
    
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> s_i;
        if (s_i == 'Y') {
            return "Four";
        }
    }
    return "Three";
}

int main() {  
    std::cout << ABC089B(); 
    return 0;
}