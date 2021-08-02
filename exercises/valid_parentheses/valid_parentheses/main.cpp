// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

#include <stack>
#include <string>

bool EvaluateExercise(std::string s) { 
    std::stack<char> parenthesesStack;
    for (const char p : s) {
        switch (p) {
            case '(':
            case '{':
            case '[':
                parenthesesStack.push(p);
                break;
            case ')':
                if (parenthesesStack.empty()) return false;
                if (parenthesesStack.top() != '(') {
                    return false;
                } else {
                    parenthesesStack.pop();
                }
                break;
            case ']':
                if (parenthesesStack.empty()) return false;
                if (parenthesesStack.top() != '[') {
                    return false;
                } else {
                    parenthesesStack.pop();
                }
                break;
            case '}':
                if (parenthesesStack.empty()) return false;
                if (parenthesesStack.top() != '{') {
                    return false;
                } else {
                    parenthesesStack.pop();
                }
                break;
        }
    }
    return parenthesesStack.empty();
}

int main(int argc, char* argv[]) {
    const int expectedArgc = 1;
    if (argc < expectedArgc + 1) {
        spdlog::error("Invalid argument count, expected {}, given {}",
                      expectedArgc, argc - 1);
        return 1;
    }
    auto input = std::string(argv[1]);
    auto result = EvaluateExercise(input);

    spdlog::info("{}", result);

    return 0;
}
