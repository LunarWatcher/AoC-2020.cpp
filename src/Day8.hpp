#pragma once

#include "util/Loader.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc {

class Day8 {
private:
    std::vector<std::string> program = loadFile("day8.txt");
    int runProgram(const std::vector<std::string>& program) {
        int ptr = 0;
        int accumulator = 0;
        std::vector<int> exhausted;
        while (true) {
            exhausted.push_back(ptr);
            auto& line = program.at(ptr);
            std::stringstream ss(line);
            std::string code, num;
            std::getline(ss, code, ' ');
            std::getline(ss, num, ' ');
            int value = std::stoi(num);

            switch (code[0]) {
            case 'n':
                ++ptr;
                break;
            case 'a':
                accumulator += value;
                ++ptr;
                break;
            case 'j':
                ptr += value;
                break;
            }
            if (std::find(exhausted.begin(), exhausted.end(), ptr) != exhausted.end()) {
                break;
            }
        }
        return accumulator;
    }

public:
    void part1() {
        std::cout << "Part 1: " << runProgram(program) << std::endl;
    }

    void part2() {
        throw std::runtime_error("Fuck intcode");
        std::vector<std::string> c{program};
        for (size_t i = c.size() - 1; i >= 0; --i) {
            if (c.at(i).starts_with("jmp")) {
                auto line = c.at(i);
                std::stringstream stream(line);
                std::string value;
                std::getline(stream, value, ' ');

                value = "";
                std::getline(stream, value, ' ');
                int iValue = std::stoi(value);
                if (i + iValue + 1 < c.size() && c[i + iValue + 1].starts_with("jmp")) {
                    c[i] = std::string("nop ") + value;
                    break;
                }
            }
        }
        std::cout << "Part 2: " << runProgram(c) << std::endl;
    }

    void run() {
        part1();
        part2();
    }
};
} // namespace aoc
