// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <string>
#include <vector>

bool isOp(const std::string& str) {
    if (str.size() > 1) {
        return false;
    }
    char ch = str[0];
    return ch == '/' || ch == '*' || ch == '+' || ch == '-';
}

int solveForOperand(const std::string& str, int left, int right) {
    switch (str[0]) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
    }
    return 0;
}

int evalRPN(std::vector<std::string>& tokens) {
    // last item ensured to be an op
    auto currIt = tokens.end() - 1;

    while (tokens.size() > 1) {
        auto leftOperand = currIt - 2;
        if (isOp(*leftOperand)) {
            currIt = leftOperand;
            continue;
        }
        auto rightOperand = currIt - 1;
        if (isOp(*rightOperand)) {
            currIt = rightOperand;
            continue;
        }
        // both operands are numbers
        int newValue = solveForOperand(*currIt, std::stoi(*leftOperand),
                                       std::stoi(*rightOperand));

        *currIt = std::to_string(newValue);

        currIt = tokens.erase(leftOperand, currIt);

        if (tokens.size() == 1) {
            continue;
        }
        currIt += 2;
    }
    return std::stoi(tokens[0]);
}

int main(int argc, char* argv[]) {
    std::vector<std::string> input{"10", "6", "9",  "3", "+", "-11", "*",
                                   "/",  "*", "17", "+", "5", "+"};

    auto result = evalRPN(input);

    spdlog::info("{}", result);

    return 0;
}
