// Copyright (c) 2021 Emmanuel Arias
#include <spdlog/spdlog.h>

#include <array>
#include <algorithm>
#include <string>

/*
 * Assuming ASCII, problem assumes not case sensitivy, ignore non-letter chars
 *
 * By definition a palindrome is like a mirror, a character is going to be
 * mirrored, with the exception of the letter at the center. What we can do here
 * is to count all character appereances and check that at least one appereance is odd
 *
 * Example:
 *
 * taco cat
 *
 * tacocat
 *
 * o is at the center so its count is going to be 1
 * t, a, and c appeards 2 times each
 *
 * laol
 *
 * int this case, l has an even count, but a and o both have uneven counts, this
 * cannot be palindrom
 *
 * Since a permutation is just the same characters in a different order we can
 * use this premise as well
 *
 * Time complexity O(N)
 * Memory complexity O(N). A small optimization here is to use a unsigned int as lookupArr, given
 * that we only have 26 letters and, instead of counting we can toggle bit on and off.
 */
bool IsPermutationOfPalindrome(const std::string& inputStr) {
    std::array<int, ('z' - 'a' + 1)> lookupArr;
    lookupArr.fill(0);

    for (char c : inputStr) {
        if (c >= 'a' && c <= 'z') {
            ++lookupArr[c - 'a'];
        } else if (c >= 'A' && c <= 'Z') {
            ++lookupArr[c - 'A'];
        }
    }

    int numUnevenCounts = std::count_if(lookupArr.begin(), lookupArr.end(),
                                        [](int i) { return i % 2 == 1; });
    return numUnevenCounts <= 1;
}

int main(int argc, char* argv[]) {
    std::string inputStr = "Tact Coa";
    spdlog::info("{} is unique: {}", inputStr,
                 IsPermutationOfPalindrome(inputStr));

    inputStr = "Tact Coal";
    spdlog::info("{} is unique: {}", inputStr,
                 IsPermutationOfPalindrome(inputStr));

    inputStr = "pizza";
    spdlog::info("{} is unique: {}", inputStr,
                 IsPermutationOfPalindrome(inputStr));

    inputStr = "darar";
    spdlog::info("{} is unique: {}", inputStr,
                 IsPermutationOfPalindrome(inputStr));

    return 0;
}
