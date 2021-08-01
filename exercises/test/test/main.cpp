// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

int EvaluateExercise(int input) { return 0; }

int main(int argc, char* argv[]) {
    const int expectedArgc = 2;
    if (argc < expectedArgc + 1) {
        spdlog::error("Invalid argument count, expected {}, given {}",
                      expectedArgc, argc - 1);
        return 1;
    }
    auto input = CastInput(argv[1]);
    if (!input) {
        spdlog::error("Invalid input for problem's input");
        return 1;
    }
    auto expectedResult = CastInput(argv[2]);
    if (!expectedResult) {
        spdlog::error("Invalid input for expected result");
        return 1;
    }

    auto result = EvaluateExercise(input.value());
    if (result == expectedResult.value()) {
        spdlog::info("Exercise has passed");
        return 0;
    }

    return 1;
}
