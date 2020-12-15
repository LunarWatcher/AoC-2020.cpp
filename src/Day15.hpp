#pragma once

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

namespace aoc {

class Day15 {
private:
    std::vector<size_t> input = {
#include "../input/day15.txt"
    };
public:
    void playElfGame(size_t cap = 2020) {
        std::unordered_map<size_t, std::vector<size_t>> lastTurnSpotted;

        size_t lastNum = 0;
        for (size_t i = 0; i < cap; ++i) {
            if (i < input.size()) {
                lastTurnSpotted[input.at(i)].push_back(i + 1);
                lastNum = input.at(i);
                continue;
            }
            auto& vec = lastTurnSpotted[lastNum];
            if (vec.size() < 2) {
                lastNum = 0;
            } else {
                lastNum = vec.back() - vec[vec.size() - 2];
            }
            lastTurnSpotted[lastNum].push_back(i + 1);
        }
        std::cout << "Part " << (cap == 2020 ? 1 : 2) << ": " << lastNum << std::endl;
    }

    void run() {
        playElfGame();
        playElfGame(30000000);
    }
};

} // namespace aoc
