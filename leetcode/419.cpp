#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> x_moves = {0, 1, 0, -1};
    vector<int> y_moves = {1, 0, -1, 0};

    int countBattleships(vector<vector<char>>& board) {
        int ans = 0;
        int n = board.size(), m = board[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == '.') continue;
                ans++;
                queue<pair<int, int>> q;
                q.push({i, j});

                while (!q.empty()) {
                    int curr_i = q.front().first, curr_j = q.front().second;
                    board[curr_i][curr_j] = '.';
                    q.pop();
                    for (int mx = 0; mx < 4; mx++) {
                        int new_i = curr_i + x_moves[mx];
                        int new_j = curr_j + y_moves[mx];
                        if ((new_i < 0) || (new_i >= n)) continue;
                        if ((new_j < 0) || (new_j >= m)) continue;
                        if (board[new_i][new_j] == 'X') {
                            q.push({new_i, new_j});
                        }
                    }
                }
            }
        }
        return ans;
    }
};