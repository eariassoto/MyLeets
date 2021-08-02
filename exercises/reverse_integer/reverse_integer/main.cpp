// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

#include <cstdint>
#include <limits>

int EvaluateExercise(int x) {
    bool isNegative = false;

    if (x == std::numeric_limits<int32_t>::max() ||
        x == std::numeric_limits<int32_t>::min()) {
        return 0;
    }

    int aux = x;
    if (x < 0) {
        aux *= -1;
        isNegative = true;
    }

    int res = 0;
    for (; aux > 0; aux = aux / 10) {
        if (res > std::numeric_limits<int32_t>::max() / 10) {
            return 0;
        }
        res *= 10;

        if (res > (std::numeric_limits<int32_t>::max() - (aux % 10))) {
            return 0;
        }
        res += (aux % 10);
    }

    if (isNegative) {
        res *= -1;
    }
    return res;
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
    spdlog::info(result);

    return 0;
}
