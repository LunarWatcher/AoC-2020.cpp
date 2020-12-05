#pragma once

#include "util/Loader.hpp"
#include <cstdio>
#include <iostream>
#include <math.h>
#include <memory_resource>
#include <string>
#include <vector>

namespace aoc {

class Day5 {
private:
    std::vector<std::string> boardingPasses = loadFile("day5.txt");
            //{"FBFBBFFRLR"};

public:
    int binSearch(const std::string& haystack, int start, int end, int lower, int upper) {
        int row;
        for (int i = start; i < end; i++) {
            switch (haystack[i]) {
            case 'F':
            case 'L':
                if (i == end - 1) {
                    row = std::min(upper, lower);
                } else
                    upper = lower + std::floor((upper - lower) / 2.0);
                break;
            case 'B':
            case 'R':
                if (i == end - 1) {
                    row = std::max(upper, lower);
                } else
                    lower = upper - std::floor((upper - lower) / 2.0);
                break;
            }
        }

        return row;
    }

    int part1() {

        int high = 0;

        for (auto& pass : boardingPasses) {
            int row = binSearch(pass, 0, 7, 0, 127);
            int seat = binSearch(pass, 7, 10, 0, 7);
            int seatID = row * 8 + seat;
            if (seatID > high)
                high = seatID;
        }

        return high;
    }

    int part2() {

        std::vector<int> ids;
        for (auto& pass : boardingPasses) {
            int row = binSearch(pass, 0, 7, 0, 127);
            int seat = binSearch(pass, 7, 10, 0, 7);
            if (row != 0 && row != 127)
                ids.push_back(row * 8 + seat);
        }
        std::sort(ids.begin(), ids.end());

        for (int i = 0; i < ids.size() - 1; i++) {
            if (ids.at(i) != ids.at(i + 1) - 1) {
                return ids.at(i) + 1;
            }
        }
        return -1;
    }

    void run() {
        std::cout << "Part 1: " << part1() << "\nPart 2: " << part2() << std::endl;
    }
};

} // namespace aoc

