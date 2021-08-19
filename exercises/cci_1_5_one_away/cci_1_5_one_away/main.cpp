// Copyright (c) 2021 Emmanuel Arias
#include <spdlog/spdlog.h>

/*
 *
 * We can split this problem in three cases:
 *
 * If the strings are the same size, we check that only one edit happened
 *
 * If the second string is shorter we first try to find the first letter than
 * changed and then we look that the rest of the letters are the same For
 * example
 *
 * $
 * please
 * $
 * plase
 *
 * p both sides, we move
 *
 *  $
 * please
 *  $
 * plase
 *
 * same case,
 *
 *   $
 * please
 *   $
 * plase
 *
 * here e and a are not equals so we move the index and check for equality
 *
 *    $
 * please
 *   $
 * plase
 *
 * now a and a are equals, and we move and check until the end
 *
 * For the case where the second string is longer than the first, we re use this
 * algorithm but flip inputs
 *
 */

bool IsOneEditAway(const std::string& original, const std::string& modified) {
    int editsCount = 0;
    for (int i = 0; i < (int)original.size(); ++i) {
        if (original[i] != modified[i]) {
            ++editsCount;
        }
    }
    return editsCount == 1;
}

bool IsOneLetterDifferent(const std::string& original,
                          const std::string& modified) {
    int auxIndex = 0;
    for (; auxIndex < (int)modified.size(); ++auxIndex) {
        if (original[auxIndex] != modified[auxIndex]) {
            // found first difference
            break;
        }
    }
    for (; auxIndex < (int)modified.size(); ++auxIndex) {
        if (original[auxIndex + 1] != modified[auxIndex]) {
            return false;
        }
    }
    return true;
}

bool IsOneChangeAway(const std::string& original, const std::string& modified) {
    if (original.size() == modified.size()) {
        return IsOneEditAway(original, modified);
    } else if (original.size() == (modified.size() + 1)) {
        return IsOneLetterDifferent(original, modified);
    } else if (original.size() == (modified.size() - 1)) {
        return IsOneLetterDifferent(modified, original);
    }

    return false;
}

int main(int argc, char* argv[]) {
    std::string original = "apple";
    std::string modified = "appl3";

    spdlog::info("Is [{}] one change away from [{}]: {}", original, modified,
                 IsOneChangeAway(original, modified));

    original = "people";
    modified = "pople";

    spdlog::info("Is [{}] one change away from [{}]: {}", original, modified,
                 IsOneChangeAway(original, modified));

    original = "pear";
    modified = "pears";

    spdlog::info("Is [{}] one change away from [{}]: {}", original, modified,
                 IsOneChangeAway(original, modified));

    original = "pizza";
    modified = "p1zzas";

    spdlog::info("Is [{}] one change away from [{}]: {}", original, modified,
                 IsOneChangeAway(original, modified));

    original = "bread";
    modified = "brea";

    spdlog::info("Is [{}] one change away from [{}]: {}", original, modified,
                 IsOneChangeAway(original, modified));

    return 0;
}
