// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <queue>
#include <string>
#include <vector>

void generateNextCombination(std::queue<std::string>& letterCombinations,
                             const std::string& digits) {
    const std::string& currCombination = letterCombinations.front();

    char nextDigit = digits[currCombination.size()];

    switch (nextDigit) {
        case '2': {
            letterCombinations.push(currCombination + 'a');
            letterCombinations.push(currCombination + 'b');
            letterCombinations.push(currCombination + 'c');
        } break;
        case '3': {
            letterCombinations.push(currCombination + 'd');
            letterCombinations.push(currCombination + 'e');
            letterCombinations.push(currCombination + 'f');
        } break;
        case '4': {
            letterCombinations.push(currCombination + 'g');
            letterCombinations.push(currCombination + 'h');
            letterCombinations.push(currCombination + 'i');
        } break;
        case '5': {
            letterCombinations.push(currCombination + 'j');
            letterCombinations.push(currCombination + 'k');
            letterCombinations.push(currCombination + 'l');
        } break;
        case '6': {
            letterCombinations.push(currCombination + 'm');
            letterCombinations.push(currCombination + 'n');
            letterCombinations.push(currCombination + 'o');
        } break;
        case '7': {
            letterCombinations.push(currCombination + 'p');
            letterCombinations.push(currCombination + 'q');
            letterCombinations.push(currCombination + 'r');
            letterCombinations.push(currCombination + 's');
        } break;
        case '8': {
            letterCombinations.push(currCombination + 't');
            letterCombinations.push(currCombination + 'u');
            letterCombinations.push(currCombination + 'v');
        } break;
        case '9': {
            letterCombinations.push(currCombination + 'w');
            letterCombinations.push(currCombination + 'x');
            letterCombinations.push(currCombination + 'y');
            letterCombinations.push(currCombination + 'z');
        } break;
    }
}

std::vector<std::string> letterCombinations(std::string digits) {
    if (digits.empty()) {
        return {};
    }

    std::vector<std::string> finalCombinations;
    std::queue<std::string> letterCombinations;

    // First one to kickstart the process
    letterCombinations.push("");

    while (!letterCombinations.empty()) {
        const std::string& currCombination = letterCombinations.front();
        if (currCombination.size() == digits.size()) {
            finalCombinations.push_back(currCombination);
        } else {
            generateNextCombination(letterCombinations, digits);
        }

        letterCombinations.pop();
    }
    return finalCombinations;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> result = letterCombinations("23");
    for (const std::string& str : result) {
        spdlog::info("{}", str);
    }

    return 0;
}
