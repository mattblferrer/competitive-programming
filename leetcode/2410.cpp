#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& players, vector<int>& trainers) {
        sort(players.begin(), players.end());
        sort(trainers.begin(), trainers.end());
        int ans = 0, ctr = 0;

        for (int i = 0; i < players.size(); i++) {
            if (ctr >= trainers.size()) break;
            while (players[i] > trainers[ctr] && ctr < trainers.size() - 1) ctr++;
            if (players[i] <= trainers[ctr]) {
                ans++;
                ctr++;
            }
        }
        return ans;
    }
};