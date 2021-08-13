// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

/* URLify
 * This is a classic problem of in-place string replacement, we know that we
 * will replace ' ' for "%20", this means for each char we will move the rest of
 * the string 2 extra spaces We also know that we have enough space in the
 * memory to do the replacement
 *
 * First we need to count how many spaces we are replacing so that we can play
 * with pointers and replace from the end to the beggining
 *
 * Example
 *
 * "Hello World 123    ", 15
 *
 * First we count 2 spaces, so the final size will be 19 characters
 *
 * Aux pointers $  #
 *
 *                $   #
 * "Hello World 123    "
 *
 * 3 is not space, copy and shift
 *
 *               $   #
 * "Hello World 123   3"
 *
 * same with 2
 *
 *              $   #
 * "Hello World 123  23"
 *
 * and 1
 *
 *             $   #
 * "Hello World 123 123"
 *
 * now the interesting we have a space, here we replace the space and move the #
 * pointer 2 extra spaces this time
 *
 *            $ #
 * "Hello World 1%20123"
 *
 * and keep doing it until $ gets all the way to the front
 * 
 * Time Complexity: O(N) where N is the total size of the string
 * Memory complexity: O(1) replacement happens in-place
 */

void URLifyString(std::string& inputStr, int originalLength) {
    // 2 extra counts from ' ' to "%20"
    const int replaceStrExtraCount = 2;
    // Do not count extra memory because it could be ' '
    int numSpaces = std::count(inputStr.begin(), inputStr.begin() + originalLength, ' ');

    int auxOriginal = originalLength - 1;
    // Second pointer gets shifted to count the extra memory, this also ensures no overlap when
    // replacing from back to front
    int auxReplaceEnd = auxOriginal + (numSpaces * replaceStrExtraCount);

    while (auxOriginal >= 0) {
        if (inputStr[auxOriginal] == ' ') {
            inputStr[auxReplaceEnd] = '0';
            inputStr[auxReplaceEnd - 1] = '2';
            inputStr[auxReplaceEnd - 2] = '%';

            // Extra shifting
            auxReplaceEnd -= replaceStrExtraCount;
        } else {
            inputStr[auxReplaceEnd] = inputStr[auxOriginal];
            
        }
        --auxReplaceEnd;
        --auxOriginal;
    }
}

int main(int argc, char* argv[]) {
    std::string input("Hello World!  ");

    spdlog::info("Original: {}", input);

    URLifyString(input, input.size() - 2);

    spdlog::info("URLified: {}", input);

    input = "website.com/New Blog Post 1.html xxyyzzaa";

    spdlog::info("Original: {}", input);

    URLifyString(input, input.size() - 8);

    spdlog::info("URLified: {}", input);

    return 0;
}
