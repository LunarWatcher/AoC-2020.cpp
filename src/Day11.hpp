#pragma once

#include "util/Loader.hpp"
#include <algorithm>
#include <string>
#include <vector>

namespace aoc {

class Day11 {
private:
    std::vector<std::vector<int>> map =
            loadType<std::vector<int>>("day11.txt", [](const std::string& row) -> std::vector<int> {
                std::vector<int> output;
                std::transform(row.begin(), row.end(), std::back_inserter(output), [](const auto& chr) -> int {
                    switch (chr) {
                    case '.':
                        return 0;
                    case 'L':
                        return 1;
                    case '#':
                        return 2;
                    }
                    throw "Unknown char  detected (breakpoint me pl0x)";
                });
                return output;
            });

public:
    void part1() {
        auto map = this->map;
        int width = map.at(0).size();
        int height = map.size();
        auto lastMap = map;
        std::vector<std::pair<int, int>> coordOffsets = {
                {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        bool change = false;
        do {
            change = false;
            for (size_t y = 0; y < map.size(); ++y) {
                for (size_t x = 0; x < map.at(0).size(); ++x) {
                    if (lastMap.at(y).at(x) == 0)
                        continue;
                    bool occupado = false;
                    int count = 0;
                    for (auto& coordOffset : coordOffsets) {

                        int tx = x + coordOffset.first;
                        int ty = y + coordOffset.second;
                        if (tx < 0 || ty < 0 || tx >= width || ty >= height)
                            continue;

                        if (lastMap.at(ty).at(tx) == 2) {
                            occupado = true;
                            if (lastMap.at(y).at(x) == 2)
                                count++;
                            else break;
                        }
                    }

                    if (!occupado && lastMap.at(y).at(x) == 1) {
                        map.at(y).at(x) = 2;
                        change = true;
                    } else if (count >= 4 && lastMap.at(y).at(x) == 2) {
                        map.at(y).at(x) = 1;
                        change = true;
                    }
                }
            }
            lastMap = map;

            // for (auto& row : map) {
            // for (auto& col : row) {
            // std::cout << (col == 0 ? '.' : (col == 1 ? 'L' : '#'));

            //}
            // std::cout << "\n";
            //}
            // std::cout << "\n\n";
        } while (change);
        int count = 0;
        for (auto& row : map) {
            for (auto& col : row) {
                if (col == 2)
                    ++count;
            }
        }
        std::cout << "Part 1: " << count << std::endl;
    }

    void part2() {
        auto map = this->map;

        int width = map.at(0).size();
        int height = map.size();
        auto lastMap = map;
        std::vector<std::pair<int, int>> coordOffsets = {
                {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        bool change = false;
        do {
            change = false;
            for (size_t y = 0; y < map.size(); ++y) {
                for (size_t x = 0; x < map.at(0).size(); ++x) {
                    if (lastMap.at(y).at(x) == 0)
                        continue;
                    bool occupado = false;
                    int count = 0;
                    for (auto& coordOffset : coordOffsets) {
                        int tx = x;
                        int ty = y;
                        do {
                            tx += coordOffset.first;
                            ty += coordOffset.second;
                            if (tx < 0 || ty < 0 || tx >= width || ty >= height)
                                break;

                            if (lastMap.at(ty).at(tx) == 2) {
                                occupado = true;
                                if (lastMap.at(y).at(x) == 2) 
                                    count++;
                                break;
                            } else if (lastMap.at(ty).at(tx) == 1) break;
                        } while (true);
                    }

                    if (!occupado && lastMap.at(y).at(x) == 1) {
                        map.at(y).at(x) = 2;
                        change = true;
                    } else if (count >= 5 && lastMap.at(y).at(x) == 2) {
                        map.at(y).at(x) = 1;
                        change = true;
                    }
                }
            }
            lastMap = map;

        } while (change);
        int count = 0;
        for (auto& row : map) {
            for (auto& col : row) {
                if (col == 2)
                    ++count;
            }
        }
        std::cout << "Part 2: " << count << std::endl;
    }

    void run() {
        part1();
        part2();
    }
};

} // namespace aoc
