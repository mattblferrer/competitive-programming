class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<string> st;
        vector<string> operators = {"+", "-", "*", "/"};
        for (int i = 0; i < tokens.size(); i++) {
            char op = ' ';
            int val1, val2;
            for (string s : operators) {
                if (tokens[i] == s) {
                    val2 = stoi(st.top());
                    st.pop();
                    val1 = stoi(st.top());
                    st.pop();
                    op = s[0];
                    break;
                }
            }

            if (op == '+') st.push(to_string(val1 + val2));
            else if (op == '-') st.push(to_string(val1 - val2));
            else if (op == '*') st.push(to_string(val1 * val2));
            else if (op == '/') st.push(to_string(val1 / val2));
            else st.push(tokens[i]);
        }
        return stoi(st.top());
    }
};