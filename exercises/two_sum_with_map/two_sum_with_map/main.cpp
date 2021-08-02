// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

#include <map>
#include <vector>

std::vector<int> EvaluateExercise(const std::vector<int>& nums, int target) {
    std::vector<int> values(2, 0);
    std::map<int, int> mappedValues;
    for (int i = 0; i < (int)nums.size(); ++i) {
        if (mappedValues.empty()) {
            mappedValues.emplace(nums[i], i);
            continue;
        }

        int valueToFind = target - nums[i];
        auto it = mappedValues.find(valueToFind);
        if (it == mappedValues.end()) {
            mappedValues.emplace(nums[i], i);
            continue;
        }

        values[0] = it->second;
        values[1] = i;
        return values;
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
