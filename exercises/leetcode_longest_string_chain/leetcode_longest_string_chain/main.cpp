// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <limits>
#include <vector>
#include <string>
#include <map>

/*
 * To check if one string w1 is predecesor or another one w2, we can take w2 and
 * remove characters until we find a match if any. So for example, take w1: ab
 * w2: acb
 *
 * if we remove [0] from w2, we get cb, do not match
 * if we remove [1] from w2, we get ab, we have a match, then w1 is predecesor
 * of w2
 *
 * The next step will be grouping our words by size, so we can go from length 2
 * and above. We could either:
 *
 * sort the array and have an array of iterators
 *
 * or
 *
 * have a hashmap with the length for key, and an array of strings as value
 *
 * once we have that we will start trying to make a chain, starting with chain
 * size = 1
 *
 * for this we will use recursivity, our stop condition will be that our current
 * word is not predecesor of any other word, it that is the case, record the
 * chain length and return.
 *
 * If the word has a succesor, then we call the function again for each
 * predecessor with this word and add 1 to the local chain count
 *
 *
 * let's do it with the example:
 *
 * words = ["a","b","ba","bca","bda","bdca"]
 *
 * the first recursive call will be
 *
 * word:a
 * chain:1
 *
 * a is a predecesor of ba, so let's continue that path
 *
 * word a -> ba
 * chain:2
 *
 * ba is a predecesor of bca, so  let's go one more step in
 *
 * word: a -> ba -> bca
 * chain:3
 *
 * bca is a predecesor of bcda, so one more step:
 *
 * a -> ba -> bca -> bdca
 * chain:4
 *
 * bcda is not a predecesor, so we stop here and record
 *
 * max_chain:4
 *
 * backtracking, we have ba to be a predecesor of bda
 *
 * word: a -> ba -> bda
 * chain:3
 *
 * turns out bda it is also a predecesor of bdca
 * a -> ba -> bca -> bdca
 * chain:4
 *
 * still, max_chain is 4
 *
 * the branch of b will give us similar results
 */

bool isPredecesor(const std::string& w1, const std::string& w2) {
    std::string aux;
    for (int i = 0; i < (int)w2.size(); ++i) {
        aux = w2;  // copy str, may be expensive
        aux.erase(i, 1);
        if (w1.compare(aux) == 0) {
            return true;
        }
    }
    // no matches found
    return false;
}

int longestStrChainRec(
    const std::string& word, int currentChainSize,
    const std::map<int, std::vector<std::string>>& lookupMap) {
    auto it = lookupMap.find(word.size() + 1);
    if (it == lookupMap.end()) {
        // no match found
        return currentChainSize;
    }
    int auxCurrent = currentChainSize;
    // else we found possible matches
    const std::vector<std::string>& nextSizeWords = it->second;
    for (const std::string& nextSizeWord : nextSizeWords) {
        if (isPredecesor(word, nextSizeWord)) {
            // can continue chain, keep calling
            int newCurrent = longestStrChainRec(
                nextSizeWord, currentChainSize + 1, lookupMap);
            auxCurrent = std::max(auxCurrent, newCurrent);
        }
    }
    return auxCurrent;
}

int longestStrChain(std::vector<std::string>& words) {
    if (words.empty()) {
        return 0;
    }

    std::map<int, std::vector<std::string>> lookupMap;

    // Group by string length
    for (const std::string word : words) {
        lookupMap[word.size()].push_back(word);
    }

    int longestChain = 1;
    for (const std::string word : words) {
        // recursive call
        int newLongest = longestStrChainRec(word, 1, lookupMap);
        longestChain = std::max(longestChain, newLongest);
    }

    return longestChain;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> words = {
        "ksqvsyq", "ks",       "kss",        "czvh",  "zczpzvdhx",
        "zczpzvh", "zczpzvhx", "zcpzvh",     "zczvh", "gr",
        "grukmj",  "ksqvsq",   "gruj",       "kssq",  "ksqsq",
        "grukkmj", "grukj",    "zczpzfvdhx", "gru"};
    int result = longestStrChain(words);
    spdlog::info("{}", result);

    return 0;
}
