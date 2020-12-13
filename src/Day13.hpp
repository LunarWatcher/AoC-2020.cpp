#pragma once

#include "util/Loader.hpp"
#include <map>
#include <numeric>
#include <string>
#include <algorithm>
#include <iostream>
#include "util/Operators.hpp"

namespace aoc {

class Day13 {
private:
    std::vector<std::string> rawData = loadFile("day13.txt");

    std::vector<int> ids;
    std::vector<int> allItems;
    int earliestDeparture;
public:
    Day13() {
        this->earliestDeparture = std::stoi(rawData.at(0));
        std::string tmp;
        std::stringstream stream(rawData.at(1));

        while (std::getline(stream, tmp, ',')) {
            if (tmp.size() && tmp != "x") {
                ids.push_back(std::stoi(tmp));
                allItems.push_back(ids.back());
            } else {
                allItems.push_back(1);
            }
        }
    }

    void part1() {
        int i = earliestDeparture;
        do {

            for (auto& id : ids) {
                if (i % id == 0) {

                    std::cout << "Part 1: " << (i - earliestDeparture) * id << std::endl;
                    return;
                }
            }
            ++i;
        } while (true);

    }

    void part2() {

        long long M = std::accumulate(allItems.begin(), allItems.end(), 1ll, std::multiplies());
        std::cout << "M = " << M << std::endl; 
        long long x = 0ll;
        long long remainder = 1;
        for (int& _y : allItems) {
            long long y(_y);
            remainder--;
            if (y == 1) continue;

            long long N = M / (long long) y;

            auto a = 0ll;
            do {
                ++a;
            } while ((a * N) % y != 1);
            std::cout << y << ": N = " << N << ", N^-1 = " << a << ", y = " << (remainder mod y) << std::endl;
            x += (a * N * (remainder mod y));

        }
        
        std::cout << "Part 2: " << (x mod M) << std::endl;
    }

    void run() {
        part1();
        part2();
    }
};

}
