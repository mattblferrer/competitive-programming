#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> scoreValidator(vector<string>& events) {
        int score = 0, counter = 0;
        for (int i = 0; i < events.size(); i++) {
            string e = events[i];
            if (e == "1") score += 1;
            if (e == "2") score += 2;
            if (e == "3") score += 3;
            if (e == "4") score += 4;
            if (e == "6") score += 6;
            if (e == "W") counter += 1;
            if (e == "WD") score += 1;
            if (e == "NB") score += 1;
            if (counter == 10) break;
        }
        return {score, counter};
    }
};