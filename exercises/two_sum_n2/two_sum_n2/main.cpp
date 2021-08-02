// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

#include <vector>

std::vector<int> EvaluateExercise(const std::vector<int>& nums, int target) {
    std::vector<int> values(2, 0);
    for (auto it = nums.begin(); it != nums.end(); it++) {
        for (auto secondIt = it + 1; secondIt != nums.end(); secondIt++) {
            if (*it + *secondIt == target) {
                values[0] = it - nums.begin();
                values[1] = secondIt - nums.begin();
                return values;
            }
        }
    }

    return values;
}

int main(int argc, char* argv[]) {
    const int expectedArgc = 2;
    if (argc < expectedArgc + 1) {
        spdlog::error("Invalid argument count, expected {}, given {}",
                      expectedArgc, argc - 1);
        return 1;
    }
    auto input = CastInput<std::vector<int>>(argv[1]);
    if (!input) {
        spdlog::error("Invalid input for problem's input");
        return 1;
    }
    auto expectedResult = CastInput<int>(argv[2]);
    if (!expectedResult) {
        spdlog::error("Invalid input for expected result");
        return 1;
    }

    auto result = EvaluateExercise(input.value(), expectedResult.value());
    spdlog::info("[{},{}]", result[0], result[1]);

    return 0;
}
