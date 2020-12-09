#pragma once

#include "util/Loader.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

namespace aoc {

class Day9 {
private:
    std::vector<long long> numbers = loadType<long long>("day9.txt", &sastoll);
    size_t idx = 0;

public:
    void part1() {
        for (size_t i = 25; i < numbers.size(); ++i) {
            std::vector<long long> preamble(numbers.begin() + (i - 25), numbers.begin() + i);

            long long target = numbers.at(i);
            bool found = false;
            for (auto& num : preamble) {
                for (auto& num2 : preamble) {
                    if (num == num2)
                        continue;
                    if (num + num2 == target) {
                        found = true;
                        goto getoutofthere;
                    }
                }
            }
        getoutofthere:
            if (!found) {
                std::cout << "Part 1: " << i << " " << numbers.at(i) << std::endl;
                idx = i;
                return;
            }
            found = false;
        }
    }

    void part2() {
        throw std::runtime_error("Broken (edge cases");
        std::vector<long long> clone(numbers.begin(), numbers.end());
        clone.erase(clone.begin() + idx);
        auto target = numbers.at(idx);
        for (auto i = 0; i < numbers.size() - 202; ++i) {
            for (auto len = 2; len <= numbers.size() - 200 - i; ++len) {
                std::vector<long long> vec(numbers.begin() + i, numbers.begin() + i + len);

                long long sum = std::accumulate(vec.begin(), vec.end(), 0, std::plus<long long>());
                if (sum == target) {
                    std::cout << "Part 2: " << (*std::min_element(vec.begin(), vec.end()) 
                            + *std::max_element(vec.begin(), vec.end())) << std::endl;
                    return;
                }
            }
        }
    }

    void run() {
        part1();
        part2();
    }
};

} // namespace aoc
