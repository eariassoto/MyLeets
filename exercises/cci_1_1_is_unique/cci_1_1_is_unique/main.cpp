// Copyright (c) 2021 Emmanuel Arias
#include <spdlog/spdlog.h>

#include <array>
#include <string>

/*
* "abcdea" -> 'a', 'b', 'c', 'd', 'a'
* Each char (assumming not extended ASCII) goes from 0x00 to 0x7F
* 
* One solution is to declare a std::unordered_set<char> and:
* 1- Find the char in the set
*    If is not in set, insert it
*    If it is in the set, string is not unique, return false
* 
* But this is too much, we do not need to hash and allocate memory for a set
* We can instead have a fixed boolean array of 0xFF elements, initialized in false
* 
* Solution time complexity: O(n)
* Solution memory usage: O(1)
*/

bool IsUnique(const std::string& inputStr) { 
    std::array<bool, 128> lookupMap;
    lookupMap.fill(false);

    for (char c : inputStr) {
        if (lookupMap[c] == false) {
            // Mark char into lookup map
            lookupMap[c] = true;
        } else {
            return false;
        }
    }
    // we loop through the whole string and did not find repeated characters
    return true; 
}

int main(int argc, char* argv[]) {

    std::string inputStr = "abc1231";
    spdlog::info("{} is unique: {}", inputStr, IsUnique(inputStr));

    inputStr = "Hello World!!!";
    spdlog::info("{} is unique: {}", inputStr, IsUnique(inputStr));
    
    inputStr = "joystick";
    spdlog::info("{} is unique: {}", inputStr, IsUnique(inputStr));

    inputStr = "freeze";
    spdlog::info("{} is unique: {}", inputStr, IsUnique(inputStr));

    return 0;
}
