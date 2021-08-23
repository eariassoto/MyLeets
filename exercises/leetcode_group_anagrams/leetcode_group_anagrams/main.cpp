// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <array>
#include <map>

#include <string>
#include <vector>

/*
* In this exercise, a key point is the fact that all strings are made out of lowercase
* letters, this means we have only 26 possible inputs. For each anagram we can count the
* letters and create a repetitions array.
* 
* For example:
* 
* "aaabbcz" -> 3,2,1,0,0,0...,1
* 
* We can use this repetitions array as a hash map key.
* 
* From then we can calculate the hash for each string and add it to a hash map containing a vector
* of strings.
* Finally we iterate the hashmap and build up the output array.
*/

typedef std::array<unsigned int, 26> Alphabet;

void fillAlphabetFromString(const std::string& input, Alphabet& key) {
    key.fill(0);
    for (const char ch : input) {
        ++key[ch - 'a'];
    }
}

std::vector<std::vector<std::string>> groupAnagrams(
    std::vector<std::string>& strs) {
    Alphabet key;

    std::map<Alphabet, std::vector<std::string>> dictionary;
    for (const std::string str : strs) {
        fillAlphabetFromString(str, key);
        dictionary[key].push_back(str);
    }

    std::vector<std::vector<std::string>> output;
    for (const auto& [key, value] : dictionary) {
        output.push_back(value);
    }
    return output;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};

    auto result = groupAnagrams(strs);
    spdlog::info("{}", result.size());

    return 0;
}
