#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <map>

using namespace std;

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        default: throw runtime_error("Invalid operator");
    }
}

queue<string> infixToRPN(const string& expression) {
    stack<char> operators;
    queue<string> output;
    stringstream numBuffer;

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];

        if (isdigit(ch) || ch == '.') {
            numBuffer << ch;
        } else {
            if (!numBuffer.str().empty()) {
                output.push(numBuffer.str());
                numBuffer.str("");
            }

            if (isOperator(ch)) {
                while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                    output.push(string(1, operators.top()));
                    operators.pop();
                }
                operators.push(ch);
            } else if (ch == '(') {
                operators.push(ch);
            } else if (ch == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    output.push(string(1, operators.top()));
                    operators.pop();
                }
                if (!operators.empty() && operators.top() == '(') {
                    operators.pop();
                } else {
                    throw runtime_error("Mismatched parentheses");
                }
            }
        }
    }

    if (!numBuffer.str().empty()) {
        output.push(numBuffer.str());
    }

    while (!operators.empty()) {
        if (operators.top() == '(') throw runtime_error("Mismatched parentheses");
        output.push(string(1, operators.top()));
        operators.pop();
    }

    return output;
}

double evaluateRPN(queue<string> rpn) {
    stack<double> operands;

    while (!rpn.empty()) {
        string token = rpn.front();
        rpn.pop();

        if (isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) {
            operands.push(stod(token));
        } else if (isOperator(token[0])) {
            if (operands.size() < 2) throw runtime_error("Invalid expression");
            double b = operands.top(); operands.pop();
            double a = operands.top(); operands.pop();
            operands.push(calculate(a, b, token[0]));
        } else {
            throw runtime_error("Invalid token in RPN");
        }
    }

    if (operands.size() != 1) throw runtime_error("Invalid expression");
    return operands.top();
}

void calculator() {
    string input;

    while (true) {
        cout << "Enter expression: ";
        getline(cin, input);

        if (input == "exit") break;

        try {
            queue<string> rpn = infixToRPN(input);
            double result = evaluateRPN(rpn);
            cout << "Result: " << result << "\n";
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

int main() {
    calculator();
    return 0;
}
