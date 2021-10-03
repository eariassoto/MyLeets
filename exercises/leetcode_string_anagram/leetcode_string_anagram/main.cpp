// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

/*

Given two strings s and p, return an array of all the start indices of p's
anagrams in s. You may return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different
word or phrase, typically using all the original letters exactly once.

We can solve this problem with a fixed window strategy, we know that we need to
find substrings for size p

First we fill out a hash map with the repetition of the characters of p, for
example,

for
s = "cbaebabacd", p = "abc"

we have the hashmap as
repetitionsP = { {a:1}, {b:1}, {c:1} }

now we have another hashmap to compare while we move the window

first, we setup the first window, this means we fill the map with the first N
characters, being N the lenght of P


     s = "cbaebabacd"
window =  ***
comparisonHashMap = { {a:1}, {b:1}, {c:1} }

we compare hashmaps, we have a match, add it to output

move the window, add the new char in the tail, remove the one in the head


     s = "cbaebabacd"
window =   ***
comparisonHashMap = { {a:1}, {b:1}, {e:1} }

hashmaps do not match, continue like so until the end

*/

void AddCharToMap(std::unordered_map<char, size_t>& lookupMap, char ch) {
    ++lookupMap[ch];
}

void RemoveCharFromMap(std::unordered_map<char, size_t>& lookupMap, char ch) {
    if (lookupMap[ch] == 1) {
        lookupMap.erase(ch);
    } else {
        --lookupMap[ch];
    }
}

std::vector<int> findAnagrams(std::string s, std::string p) {
    std::vector<int> results;
    if (p.size() > s.size()) {
        return results;
    }

    size_t windowStart = 0;
    size_t windowEnd = p.size() - 1;

    std::unordered_map<char, size_t> repetitionsPMap;
    std::unordered_map<char, size_t> comparisonMap;

    for (size_t i = 0; i < p.size(); ++i) {
        ++repetitionsPMap[p[i]];
        ++comparisonMap[s[i]];
    }

    if (repetitionsPMap == comparisonMap) {
        results.push_back(windowStart);
    }

    while (windowEnd < s.size() - 1) {
        RemoveCharFromMap(comparisonMap, s[windowStart]);
        ++windowStart;

        ++windowEnd;
        AddCharToMap(comparisonMap, s[windowEnd]);

        if (repetitionsPMap == comparisonMap) {
            results.push_back(windowStart);
        }
    }

    return results;
}

int EvaluateExercise(int input) { return 0; }

int main(int argc, char* argv[]) {
    std::string input = "cbaebabacd";

    auto result = findAnagrams(input, "abc");
    for (const int index : result) {
        spdlog::info("{}", index);
    }

    return 0;
}
