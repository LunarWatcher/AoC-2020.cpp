#pragma once
#include <vector>
#include <string>
#include "util/Loader.hpp"
#include <iostream>

namespace aoc {

class Day3 {
private:
    std::vector<std::string> rawData = aoc::loadFile("day3.txt");
    std::vector<std::vector<bool>> mapData;
public:
    Day3() {
        for (auto& line : rawData) {
            mapData.push_back({});
            for (auto& character : line) {
                mapData.back().push_back(character == '#');
            }
        }
    }

    int run(int right, int down) {
        
        size_t x = 0;
        int trees = 0;
        const size_t width = mapData[0].size();

        for (size_t i = 0; i < mapData.size() - down; i += down) {
            x = (x + right) % width;
            if (mapData[i + down][x]) {
                trees++;
            }
        }
        return trees;
    }

    int part1() {
        return run(3, 1);
    }

    int part2() {

        size_t treeMultiply = 1;
        for (int i = 1; i <= 7; i += 2) {
            treeMultiply *= run(i, 1);
        }
        treeMultiply *= run(1, 2);

        return treeMultiply;
    }

    void run() {
        std::cout << part1() << "\n" << part2() << std::endl;
    }
};

}
