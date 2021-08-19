// Copyright (c) 2021 Emmanuel Arias
#include <spdlog/spdlog.h>

#include <array>
#include <string>

/*
 * For this exercise I will assume that there is not whitespacing,
 * and that strings are case sensitive. Also assuming ASCII
 *
 * A string is a permutation of the other if they have the same string count,
 * for instance
 * cara has  1 c, 2 a, and 1 r
 * raac also has the same char count
 *
 * Based on this we can iterate the first string, adding 1 to a lookup table for
 * every time the char appears in the string. Then iterate the second string and
 * subtract 1 in the lookup table. Early return if the lookup index goes below
 * zero, this means the second string has an extra char.
 *
 * Finally iterate the lookup table, if the second string is a permutation then
 * all indexes should be zero. This is because the premutated string will cancel
 * out all char counts
 *
 * Time complexity: O(N+M) where N and M are the strings' lengths
 * Memory complexity: O(1)
 */

bool IsPermutationOf(const std::string& originalString,
                     const std::string& stringToTest) {
    if (originalString.size() != stringToTest.size()) {
        return false;
    }

    std::array<int, 128> lookupMap;
    lookupMap.fill(0);

    for (char c : originalString) {
        ++lookupMap[c];
    }

    for (char c : stringToTest) {
        int newCount = lookupMap[c]-- - 1;
        if (newCount < 0) {
            return false;
        }
    }

    for (const int count : lookupMap) {
        if (count > 0) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {

    std::string original = "pizza";

    std::string inputStr = "pizzas";
    spdlog::info("{} is permutation of {}: {}", inputStr, original,
                 IsPermutationOf(original, inputStr));

    inputStr = "zzapi";
    spdlog::info("{} is permutation of {}: {}", inputStr, original,
                 IsPermutationOf(original, inputStr));

    inputStr = "paziz";
    spdlog::info("{} is permutation of {}: {}", inputStr, original,
                 IsPermutationOf(original, inputStr));

    inputStr = "paZiZ";
    spdlog::info("{} is permutation of {}: {}", inputStr, original,
                 IsPermutationOf(original, inputStr));

    inputStr = "zzpa";
    spdlog::info("{} is permutation of {}: {}", inputStr, original,
                 IsPermutationOf(original, inputStr));

    return 0;
}
