#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string chord(std::vector<int> c) {
    int x_i = c[0];
    int y_i = c[1];
    int z_i = c[2];
    while (y_i - x_i < 0) {
        y_i += 12;
    }
    while (z_i - y_i < 0) {
        z_i += 12;
    }
    if (y_i - x_i == 4 && z_i - y_i == 3) { 
        return "major";
    }
    if (y_i - x_i == 3 && z_i - y_i == 4) { 
        return "minor";
    }
    return "strange";
}

std::string problem88A() {
    std::string chords[12] = {"C", "C#", "D", "D#", "E", "F", 
        "F#", "G", "G#", "A", "B", "H"};
    std::string x, y, z;
    std::cin >> x >> y >> z;
    std::vector<int> c = {0, 0, 0};

    for (int i = 0; i < 12; i++) {
        if (chords[i] == x) {
            c[0] = i;
        }
        if (chords[i] == y) {
            c[1] = i;
        }
        if (chords[i] == z) {
            c[2] = i;
        }
    }
    std::sort(c.begin(), c.end());
    do {
        std::string result = chord(c);
        if (result != "strange") {
            return result;
        }
    } while (std::next_permutation(c.begin(), c.end()));
    return "strange";
}

int main() {
    std::cout << problem88A();	

    return 0;
}