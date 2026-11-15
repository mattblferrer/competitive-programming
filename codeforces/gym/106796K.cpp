#include <iostream>
#include <vector>
using ll = long long;

struct Coord { ll x, y; };

struct Rect { Coord corners[4]; };

bool splittable(std::vector<Rect> rects) {
    if (rects.size() <= 1) { return true; }

    for (int i = 0; i < rects.size() - 1; i++) {
        for (int j = i + 1; j < rects.size(); j++) {
            for (int c1 = 0; c1 < 4; c1++) {
                for (int c2 = 0; c2 < 4; c2++) {
                    // corner loop
                    bool possible = true;
                    Coord a = rects[i].corners[c1], b = rects[j].corners[c2];

                    std::vector<Rect> left, right;
                    for (int k = 0; k < rects.size(); k++) {
                        int lp = 0, rp = 0;
                        for (int c3 = 0; c3 < 4; c3++) {
                            Coord c = rects[k].corners[c3];
                            ll cross = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
                            if (cross > 0) { lp++; }
                            else if (cross < 0) { rp++; }
                        }

                        if ((lp > 0) && (rp > 0)) { possible = false; break; }
                        if (lp > 0) { left.push_back(rects[k]); }
                        else { right.push_back(rects[k]); }
                    }

                    if (possible && (left.size() > 0) && (right.size() > 0)) {
                        return (splittable(left) && splittable(right));
                    }
                }
            }
        }
    }
    return false;
}

int main() {
    int n, a, b, c, d; std::cin >> n;
    std::vector<Rect> rects;
    for (int i = 0; i < n; i++) {
        std::cin >> a >> b >> c >> d;
        rects.push_back(Rect{{Coord{a, b},
                              Coord{a, d},
                              Coord{c, b},
                              Coord{c, d}}});
    }

    if (splittable(rects)) { std::cout << n - 1; }
    else { std::cout << "impossible"; }
}