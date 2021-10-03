// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <unordered_map>
#include <string>

/*
* Given a string you need to print longest possible substring that has exactly M
unique characters. If there are more than one substring of longest possible
length, then print any one of them.

Examples:

"aabbcc", k = 1
Max substring can be any one from {"aa" , "bb" , "cc"}.

"aabbcc", k = 2
Max substring can be any one from {"aabb" , "bbcc"}.

"aabbcc", k = 3
There are substrings with exactly 3 unique characters
{"aabbcc" , "abbcc" , "aabbc" , "abbc" }
Max is "aabbcc" with length 6.

"aaabbb", k = 3
There are only two unique characters, thus show error message.


For this we can use a hashmap to track how many unique characters the string has
If there are less than K, we do an early return

If we pass this check, we ensure there is at least one solution.

To find the subtring, we can use the sliding window method. we start with the
first char as the window and move towards the right side. The largest substring
might be the string itself, so we know we need to move the window at least the
size of the string.

In every step, we check if the window is not valid, if that were the case we
shrink the window to the left

*/

void AddCharToMap(std::unordered_map<char, int>& lookupMap, char ch) {
    ++lookupMap[ch];
}

void RemoveCharFromMap(std::unordered_map<char, int>& lookupMap, char ch) {
    if (lookupMap[ch] == 1) {
        lookupMap.erase(ch);
    } else {
        --lookupMap[ch];
    }
}

bool IsWindowIsValid(std::unordered_map<char, int>& lookupMap, size_t k) {
    return lookupMap.size() <= k;
}

std::string GetLargestSubstringWithKUniqueChars(const std::string& input,
                                                size_t k) {
    if (k == 0) {
        return "";
    }

    std::unordered_map<char, int> lookupMap;

    for (char ch : input) {
        ++lookupMap[ch];
    }

    if (lookupMap.size() < k) {
        return "";
    }

    // reset hash map
    lookupMap.clear();

    size_t windowStart = 0;

    size_t largestWindowSize = 1;
    size_t largestWindowStart = windowStart;

    for (size_t i = 0; i < input.size(); ++i) {
        // Add current tail of the window
        AddCharToMap(lookupMap, input[i]);

        while (!IsWindowIsValid(lookupMap, k)) {
            RemoveCharFromMap(lookupMap, input[windowStart]);
            ++windowStart;
        }

        // check if we need to store current window
        size_t currWindowSize = i - windowStart + 1;
        if (currWindowSize > largestWindowSize) {
            largestWindowSize = currWindowSize;
            largestWindowStart = windowStart;
        }
    }


    return input.substr(largestWindowStart, largestWindowSize);
}

int main(int argc, char* argv[]) {
    std::string input = "aaswqsbcc";

    auto result = GetLargestSubstringWithKUniqueChars(input, 1);
    spdlog::info("Result with k={} [{}]", 1, result);
    result = GetLargestSubstringWithKUniqueChars(input, 2);
    spdlog::info("Result with k={} [{}]", 2, result);
    result = GetLargestSubstringWithKUniqueChars(input, 3);
    spdlog::info("Result with k={} [{}]", 3, result);
    result = GetLargestSubstringWithKUniqueChars(input, 4);
    spdlog::info("Result with k={} [{}]", 4, result);
    

    return 0;
}
