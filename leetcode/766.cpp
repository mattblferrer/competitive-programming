#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        map<int, int> diag;
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (diag.count(i - j) == 0) diag[i - j] = matrix[i][j];
                else if (diag[i - j] != matrix[i][j]) return false;
            }
        }
        return true;
    }
};