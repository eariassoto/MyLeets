// Copyright (c) 2021 Emmanuel Arias
#include "input_casting.h"
#include <exception>
#include <string>

template <>
std::optional<int> CastInput(const char* input) {
    std::string inputStr(input);
    try {
        int numInput = std::stoi(inputStr);
        return numInput;
    } catch (std::exception e) {
        return {};
    }
}

template <>
std::optional<std::vector<int>> CastInput(const char* input) {
    try {
        std::string inputStr(input);
        std::vector<int> values;
        const std::string delim(",");
        auto start = 0U;
        auto end = inputStr.find(delim);
        while (end != std::string::npos) {
            values.emplace_back(std::stoi(inputStr.substr(start, end - start)));
            start = end + delim.length();
            end = inputStr.find(delim, start);
        }
        values.emplace_back(std::stoi(inputStr.substr(start, end)));
        return values;
    } catch (std::exception e) {
        return {};
    }
}
