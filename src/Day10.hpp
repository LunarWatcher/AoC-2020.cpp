#pragma once

#include <vector>
#include <string>
#include "util/Loader.hpp"
#include <iostream>
#include <map>

namespace aoc {

class Day10 {
private:
    std::vector<int> input = loadType<int>("day10.txt", &sastoi);
public:
    int part1() {
        int one = 0, three = 1;

        std::sort(input.begin(), input.end());
        int last = 0;

        for (auto& num : input) {

            if (num - last == 1) {
                one++;
            } else if (num - last == 3) {
                three++; 
            }
            last = num;
        }

        return one * three;
    }

    long long part2() {
        std::map<long long, long long> nodeCounts = {{2, 1}, {3, 2}, {4, 4}, {5, 7}, {6, 13}};
        long long sum = 1LL;
        input.insert(input.begin(), 0);
        auto max = input.back();
        input.push_back(max + 3);
        auto cumulativeOptions = 0LL;
        bool lastOne = false;
        for (auto& num : input) {
            long long options = 0LL;
            if (std::find(input.begin(), input.end(), num + 1) != input.end()) {
                options++;
            }
            if (std::find(input.begin(), input.end(), num + 2) != input.end()) {
                ++options;
            }
            if (std::find(input.begin(), input.end(), num + 3) != input.end()) {
                options++;
            }
            if (num == 8) {
                std::cout << "Breakpoint " << options << std::endl;
            }
            cumulativeOptions += 1;
            if (options == 1LL) {
                if (cumulativeOptions >= 2) {
                    if (!lastOne) {
                        lastOne = true;
                        continue;
                    }
                    lastOne = false;
                    std::cout << "Opt" << cumulativeOptions << std::endl;
                    sum *= nodeCounts.at(cumulativeOptions);
                }
                cumulativeOptions = 0LL;
                continue;
            }
        }
        return sum;
    }

    void run() {
        std::cout << "Part 1: "  << part1() << "\nPart 2: " << part2() << std::endl;
    }

};

}
