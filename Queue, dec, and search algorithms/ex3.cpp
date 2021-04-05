#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <deque>
using namespace std;


struct Operation {
    char type = 0;
    int digit = 0;
};


bool Brackets(char prev, char current) {
    return (prev == '+' || prev == '-') && (current == '*' || current == '/');
}


int main() {
    int x = 0; 
    int n = 0;
    cin >> x;
    cin >> n;
    vector<Operation> operations(n);

    for (int i = 0; i < n; i++) {
        cin >> operations[i].type;
        cin >> operations[i].digit;
    }

    deque<string> expression;
    expression.push_back(to_string(x));

    char last_operation = '*';

    for (const auto& operation : operations) {
        if (Brackets(last_operation, operation.type)) {
            expression.push_front("(");
            expression.push_back(")");
        }
        expression.push_back(" ");
        expression.push_back(string(1, operation.type));
        expression.push_back(" ");
        expression.push_back(to_string(operation.digit));
        last_operation = operation.type;
    }

    for (const string& s : expression) {
        cout << s;
    }
    return 0;
}
