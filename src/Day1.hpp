#pragma once

#include "util/Loader.hpp"
#include <iostream>
#include <string>

namespace aoc {

class Day1 {
private:
    std::vector<int> input = loadType<int>("day1.txt", [](const std::string& i) {
                return std::stoi(i);
            });
public:

    long long part1() {
        for (size_t i = 0; i < input.size() - 1; ++i) {
            for (size_t j = i + 1; j < input.size(); ++j) {
                if (input[i] + input[j] == 2020) {
                    return input[i] * input[j];
                }
            }
        }
        return -1;
    }

    long long part2() {
        for (size_t i = 0; i < input.size() - 2; ++i) {
            for (size_t j = i + 1; j < input.size() - 1; ++j) {
                for (size_t k = j + 1; k < input.size(); ++k) {
                    if (input[i] + input[k] + input[j] == 2020) {
                        return input[i] * input[j] * input[k];
                    }
                }
            }
        }
        return -1;
    }

    void run() {
        auto p1 = part1();
        auto p2 = part2();
        std::cout << "Part 1: " << p1 << "\n"
                  << "Part 2: " << p2 << std::endl;
    }

};

}
