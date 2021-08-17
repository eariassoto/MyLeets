// Copyright (c) 2021 Emmanuel Arias

#include <common_lib/input_casting.h>
#include <spdlog/spdlog.h>

#include <string>
#include <sstream>
#include <unordered_map>

/*
* This exercise seems simple but it has a tricky part when trying to calculating the
* compressed string length.
* 
* Lets say that we have:
* "helloworldlllllll" as input
* 
* We can count occurences in a hash map
* h 1
* e 1
* l 10
* o 2
* w 1
* r 1
* d 1
* 
* To calculate the compressed string beforehand, with no additional mem allocations,
* we can iterate the hash map and sum 1 + count size in chars.
* To count the size of the count we can use this algorithm
* 
* int aux = 0;
* 
* do
* {
* ++aux;
* num / 10;
* } while(num != 0)
* 
* (We use a do while to guarantee that 0 <= num < 10 gives as result 1;
* 
* We then compare sizes, and if the compressed string is smaller then we return the compressed string
* This string can also be built by running through the hashmap
* 
*/

std::string CompressString(const std::string& input) { 

    std::unordered_map<char, unsigned int> frequencyMap;

    for (const char c: input) {
        ++frequencyMap[c];
    }

    auto GetCharLengthForNumber = [](unsigned int number) -> unsigned int {
        unsigned int auxNumber = number;
        unsigned int size = 0;
        do {
            ++size;
            auxNumber /= 10;
        } while (auxNumber != 0);
        return size;
    };

    unsigned int compressedStringLength = 0;
    for (const auto& [letter, freq]: frequencyMap) {
        compressedStringLength += 1 + GetCharLengthForNumber(freq);
    }

    if (compressedStringLength >= input.size()) {
        return input;
    }

    std::stringstream answer;
    for (const auto& [letter, freq] : frequencyMap) {
        answer << letter << freq;
    }
    return answer.str();
}

int main(int argc, char* argv[]) {
    std::string input = "Hello World";
    spdlog::info("{} compressed: {}", input, CompressString(input));

    input = "abcdefg";
    spdlog::info("{} compressed: {}", input, CompressString(input));

    input = "bbbbbbbbgggggggggggggggggggg";
    spdlog::info("{} compressed: {}", input, CompressString(input));

    return 0;
}
