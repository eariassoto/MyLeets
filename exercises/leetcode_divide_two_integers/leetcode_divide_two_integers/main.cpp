// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>
#include <limits>

/*
 * Let's say we have 10 / 2
 *
 * we start the counter and add the divisdor:
 *
 * aux = 0, count = 0
 * aux = 2, count = 1
 * aux = 4, count = 2
 * aux = 6, count = 3
 * aux = 8, count = 4
 * aux = 10, count = 5
 *
 * we get the result
 *
 * in case we have 11 / 3
 *
 * aux = 0, count = 0
 * aux = 3, count = 1
 * aux = 6, count = 2
 * aux = 9, count = 3
 * aux = 12, count = 4
 *
 * but 12 is bigger so we skip it an return 3.
 *
 * What about overflow?
 *
 * if (max int) - aux + divisor < 0 -> overflow
 *
 *
 */

int divide(int dividend, int divisor) {
    if (dividend == 0) return 0;

    int aux = 0;
    int count = 0;

    const bool resultIsNeg = (dividend < 0) ^ (divisor < 0);
    if (divisor < 0) divisor *= -1;
    if (dividend < 0) dividend *= -1;

    constexpr int largestSigned = std::numeric_limits<int>::max();
    while (aux < dividend) {
        if (largestSigned - (aux + divisor) < 0) {
            return std::numeric_limits<int>::max();
        }

        // We will go over the division, finish here
        if ((aux + divisor) > dividend) {
            break;
        }

        aux += divisor;
        ++count;

        // Even division, finish here
        if (aux == dividend) {
            break;
        }
    }

    return resultIsNeg ? -count : count;
}

int main(int argc, char* argv[]) {
    auto result = divide(15, 3);

    spdlog::info("{}", result);

    return 0;
}
