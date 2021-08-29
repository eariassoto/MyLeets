// Copyright (c) 2021 Emmanuel Arias

#include <spdlog/spdlog.h>

#include <algorithm>
#include <vector>

int hIndex(std::vector<int>& citations) {
    std::sort(citations.begin(), citations.end());

    int currentIndex = 0;
    int itemsLeft = citations.size() - 1;
    while (currentIndex < (int)citations.size() &&
           itemsLeft >= citations[currentIndex]) {
        ++currentIndex;
        --itemsLeft;
    }
    return citations.size() - currentIndex;
}

int main(int argc, char* argv[]) {
    std::vector<int> input{0};

    int result = hIndex(input);

    spdlog::info("H Index is: {}", result);

    return 0;
}
