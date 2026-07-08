class Spreadsheet {
public:
    vector<vector<int>> sheet;
    Spreadsheet(int rows) {
        this->sheet.resize(26, vector<int>(rows));
    }

    void setCell(string cell, int value) {
        sheet[cell[0] - 'A'][stoi(cell.substr(1, cell.size() - 1)) - 1] = value;
    }

    void resetCell(string cell) {
        sheet[cell[0] - 'A'][stoi(cell.substr(1, cell.size() - 1)) - 1] = 0;
    }

    int getValue(string formula) {
        string cell_1, cell_2;
        int curr_cell = 1;
        for (int i = 1; i < formula.size(); i++) {
            if (formula[i] == '+') curr_cell = 2;
            else if (curr_cell == 1) cell_1 += formula[i];
            else cell_2 += formula[i];
        }
        int val_1 = 0, val_2 = 0;
        if (isalpha(cell_1[0])) {
            int col = cell_1[0] - 'A';
            int row = stoi(cell_1.substr(1, cell_1.size() - 1)) - 1;
            val_1 = sheet[col][row];
        }
        else val_1 = stoi(cell_1);
        if (isalpha(cell_2[0])) {
            int col = cell_2[0] - 'A';
            int row = stoi(cell_2.substr(1, cell_2.size() - 1)) - 1;
            val_2 = sheet[col][row];
        }
        else val_2 = stoi(cell_2);
        return val_1 + val_2;
    }
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */