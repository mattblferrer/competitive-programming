class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int neighbors = 0;
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;
                        if ((i + di) < 0 || (i + di) >= m) continue;
                        if ((j + dj) < 0 || (j + dj) >= n) continue;
                        if (board[i + di][j + dj] % 2 == 1) neighbors++;
                    }
                }
                if (board[i][j] % 2 == 1 && (neighbors == 2 || neighbors == 3)) board[i][j] += 2;
                if (board[i][j] % 2 == 0 && (neighbors == 3)) board[i][j] += 2;
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = board[i][j] / 2;
            }
        }
    }
};