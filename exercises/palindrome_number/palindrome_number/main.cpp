// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

#include <vector>

bool EvaluateExercise(int x) {
    if (x < 0) {
        return false;
    }
    if (x == 0) {
        return false;
    }
    std::vector<int> digitValues;

    int aux = x;
    while (aux != 0) {
        int newValue = aux % 10;
        digitValues.push_back(newValue);
        aux /= 10;
    }

    if (digitValues.size() == 1) {
        return true;
    }

    auto leftIt = digitValues.begin();
    auto rightIt = digitValues.end() - 1;
    while (leftIt < rightIt) {
        if (*leftIt != *rightIt) {
            return false;
        }
        leftIt++;
        rightIt--;
    }

    return true;
}

int main(int argc, char* argv[]) {
    const int expectedArgc = 1;
    if (argc < expectedArgc + 1) {
        spdlog::error("Invalid argument count, expected {}, given {}",
                      expectedArgc, argc - 1);
        return 1;
    }
    auto input = CastInput<int>(argv[1]);
    if (!input) {
        spdlog::error("Invalid input for problem's input");
        return 1;
    }

    auto result = EvaluateExercise(input.value());
    spdlog::info("{}", result);

    return 0;
}
