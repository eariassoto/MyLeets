// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <string>
#include <string_view>
#include <vector>

/*
 *
 * for this exercise we can try to break down the word into subsection from top
 * to the end.
 *
 * We start with the full word, then we iterate through all the dictionary. If
 * one word is the beggining of the current word, add the rest of the word to a
 * queue.
 *
 * If by removing the current word we end up with nothing, we know the word is a
 * combination of the dictionary word
 *
 * Lets go with an example
 *
 * Input: s = "applepenapple"
 * wordDict = ["apple","pen"]
 * queue = ["applepenapple"]
 *
 * we start with:
 * s = applepenapple
 * word = apple
 *
 * in this case we can remove apple from the beginning
 *
 * queue = ["applepenapple", "penapple"]
 *
 * s = applepenapple
 * word = pen
 *
 * here we cannot do anything so we remove the first element of the queue and
 * continue
 *
 * Input: s = "applepenapple"
 * wordDict = ["apple","pen"]
 * queue = ["penapple"]
 *
 * with
 *
 * s = penapple
 * word = apple
 * queue = ["penapple"]
 *
 * nothing to do
 *
 * s = penapple
 * word = pen
 *
 * we can remove pen, so we have
 *
 * queue = ["penapple", "apple"]
 *
 * remove the first element from the queue
 *
 * queue = ["apple"]
 *
 * go again, with
 *
 * s = apple
 * word = apple
 *
 * we remove and have an empty string
 *
 *
 */

bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    std::queue<std::string_view> decomposedWord;
    decomposedWord.push(std::string_view(s));

    std::sort(wordDict.begin(), wordDict.end(),
              [](std::string a, std::string b) { return a.size() < b.size(); });

    while (!decomposedWord.empty()) {
        const std::string_view& currDecomposed = decomposedWord.front();

        for (const std::string& w : wordDict) {
            // rest of the dictionary is useless
            if (w.size() > currDecomposed.size()) {
                break;
            }
            if (w.size() == currDecomposed.size()) {
                if (w == currDecomposed) {
                    return true;
                }
            } else {
                // w is smaller than the current decomposed word
                bool isFirstSubstr = true;
                for (size_t i = 0; i < w.size(); ++i) {
                    if (w[i] != currDecomposed[i]) {
                        isFirstSubstr = false;
                        break;
                    }
                }
                if (isFirstSubstr) {
                    // w is the first substr in decomposedWord
                    decomposedWord.push(currDecomposed.substr(w.size()));
                }
            }
        }

        decomposedWord.pop();
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::string input = "applepenapple";
    std::vector<std::string> wordDict{"apple", "pen"};

    auto result = wordBreak(input, wordDict);
    spdlog::info("{}", result);

    return 0;
}
