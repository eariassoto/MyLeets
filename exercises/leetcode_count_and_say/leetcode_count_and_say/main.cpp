// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <string>

/*
 * Exercise description:
 *
 * The count-and-say sequence is a sequence of digit strings defined by the
 * recursive formula: countAndSay(1) = "1" countAndSay(n) is the way you would
 * "say" the digit string from countAndSay(n-1), which is then converted into a
 * different digit string.
 *
 * To determine how you "say" a digit string, split it into the minimal number
 * of groups so that each group is a contiguous section all of the same
 * character. Then for each group, say the number of characters, then say the
 * character. To convert the saying into a digit string, replace the counts with
 * a number and concatenate every saying.
 *
 * Solution:
 *
 * The recursive call is quite simple:
 *
 * std::string CountAndSay(int n)
 *
 * if(n == 1)
 * {
 *      return "1";
 * }
 * else
 * {
 *     return SayString(CountAndSay(n-1));
 * }
 *
 * the interesting part here is the SayString function.
 *
 * this function will receive an array of chars (std::string), we can
 * iterate linearly holding the current char and the current char count, when a
 * new char shows up we push the count to a new string and move on
 *
 * For example, we have
 *
 * outStr = ""
 * currentChar = 0
 * currentCount = 0
 *
 * 44332
 *
 * we start with 4
 *
 * outStr = ""
 * currentChar = '4'
 * currentCount = 1
 *
 * 44332
 * $
 *
 * next iteration, we have another 4
 *
 * outStr = ""
 * currentChar = '4'
 * currentCount = 2
 *
 * 44332
 *  $
 *
 * the next iteration, we have a new character, so we push the current
 * one and update
 *
 * outStr = "24"
 * currentChar = '3'
 * currentCount = 1
 *
 * 443222
 *   $
 *
 * next iteration, new char
 *
 * outStr = "2413"
 * currentChar = '2'
 * currentCount = 1
 *
 * 443222
 *    $
 *
 * and so on,
 *
 * outStr will be the return value, we will give this to the recursive function
 */

std::string sayNumber(const std::string& input) {
    std::string outStr;

    char currentChar = 0;
    char currentCount = 0;
    // lets assume not null
    for (const char ch : input) {
        if (ch == currentChar) {
            ++currentCount;
        } else {
            if (currentChar != 0) {
                // we need to push the last value
                outStr += std::to_string(currentCount);
                outStr += currentChar;
            }
            currentChar = ch;
            currentCount = 1;
        }
    }

    // Push last value
    outStr += std::to_string(currentCount);
    outStr += currentChar;

    return outStr;
}

std::string countAndSay(int n) {
    if (n == 1) {
        return "1";
    } else {
        return sayNumber(countAndSay(n - 1));
    }
}

int main(int argc, char* argv[]) {
    int n = 4;

    auto result = countAndSay(n);
    spdlog::info("Count and say for {}: {}", n, result);

    return 0;
}
