class MinStack {
public:
    stack<pair<int, int>> s;
    int min_e;

    MinStack() {
        min_e = INT_MAX;
    }

    void push(int value) {
        min_e = min(min_e, value);
        s.push({value, min_e});
    }

    void pop() {
        s.pop();
        if (s.empty()) min_e = INT_MAX;
        else min_e = s.top().second;
    }

    int top() {
        return s.top().first;
    }

    int getMin() {
        return s.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */