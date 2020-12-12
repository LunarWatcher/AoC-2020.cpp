#pragma once

#include "util/Loader.hpp"
#include <iostream>
#include <math.h>
#include <string>
#include <utility>
#include <vector>

namespace aoc {

enum class Day12Dir { NORTH = 1, SOUTH = 3, EAST = 0, WEST = 2, LEFT = 4, RIGHT = 5, FORWARD = 6 };

class Day12 {
private:
    std::vector<std::pair<Day12Dir, int>> directions =
            loadType<std::pair<Day12Dir, int>>("day12.txt", [](const std::string& line) -> std::pair<Day12Dir, int> {
                Day12Dir dir;
                switch (line.at(0)) {
                case 'F':
                    dir = Day12Dir::FORWARD;
                    break;
                case 'R':
                    dir = Day12Dir::RIGHT;
                    break;
                case 'L':
                    dir = Day12Dir::LEFT;
                    break;
                case 'N':
                    dir = Day12Dir::NORTH;
                    break;
                case 'S':
                    dir = Day12Dir::SOUTH;
                    break;
                case 'E':
                    dir = Day12Dir::EAST;
                    break;
                case 'W':
                    dir = Day12Dir::WEST;
                    break;
                }

                return {dir, std::stoi(line.substr(1))};
            });

public:
    void part1() {
        int x = 0, y = 0;
        auto direction = static_cast<int>(Day12Dir::EAST);
        for (auto& [dir, value] : directions) {
            auto _dir = dir;
            switch (_dir) {
            case Day12Dir::LEFT:
                direction = ((direction + (value / 90)) % 4 + 4) % 4;
                break;
            case Day12Dir::RIGHT:
                direction = ((direction - (value / 90)) % 4 + 4) % 4;
                break;
            case Day12Dir::FORWARD:
                _dir = static_cast<Day12Dir>(direction);
                break;
            default:
                break;
            }
            switch (_dir) {
            case Day12Dir::EAST:
                x += value;
                break;
            case Day12Dir::WEST:
                x -= value;
                break;
            case Day12Dir::NORTH:
                y += value;
                break;
            case Day12Dir::SOUTH:
                y -= value;
                break;
            default: 
                break;
            }
        }
        
        std::cout << "Part 1: " << (std::abs(x) + std::abs(y)) << std::endl;
    }

    void part2() {

        int x = 0, y = 0;
        // Note: the waypoint coords are always relative to the ship
        int wX = 10, wY = 1;
        
        for (auto& [dir, value] : directions) {

            switch (dir) {
            case Day12Dir::LEFT:
                for (int i = 0; i < value / 90; ++i) {
                    auto cache = wY;
                    wY = wX;
                    wX = -cache;
                }
                break;
            case Day12Dir::RIGHT:
                for (int i = 0; i < value / 90; ++i) {
                    auto cache = wY;
                    wY = -wX;
                    wX = cache;
                }
                break;
            case Day12Dir::FORWARD:
                x += value * wX;
                y += value * wY;
                std::cout << x << " " << y << std::endl;
                break;
            case Day12Dir::EAST:
                wX += value;
                break;
            case Day12Dir::WEST:
                wX -= value;
                break;
            case Day12Dir::NORTH:
                wY += value;
                break;
            case Day12Dir::SOUTH:
                wY -= value;
                break;
            }
        }
        
        std::cout << "Part 2: " << (std::abs(x) + std::abs(y)) << std::endl;
    }

    void run() {
        part1();
        part2();
    }
};

} // namespace aoc
