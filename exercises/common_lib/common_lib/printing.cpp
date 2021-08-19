// Copyright (c) 2021 Emmanuel Arias
#include "printing.h"

#include <sstream>
#include <spdlog/spdlog.h>

void PrintMatrix(const std::vector<std::vector<int>>& matrix) {
    std::stringstream aux;
    aux << '\n';
    for (const auto& row : matrix) {
        for (const int col : row) {
            aux << col << " ";
        }
        aux << '\n';
    }
    spdlog::info("{}", aux.str());
}
