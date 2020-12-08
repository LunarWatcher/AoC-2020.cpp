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
    std::pair<int, bool> runProgram(const std::vector<std::string>& program) {
        int ptr = 0;
        int accumulator = 0;
        std::vector<int> exhausted;
        bool safe = true;
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
                safe = false;
                break;
            }
            if (ptr >= program.size()) break;
        }
        return {accumulator, safe};
    }

public:
    void part1() {
        std::cout << "Part 1: " << runProgram(program).first << std::endl;
    }

    void part2() {
        for (int i = 0; i < 2; ++i) {
            std::string source, target;
            if (i == 1) { source = "nop"; target="jmp"; }
            else { source = "jmp"; target = "nop"; }

            for (size_t j = 0; j < program.size(); ++j) {
                if (program.at(j).starts_with(source)) {
                    std::vector<std::string> copy(program);
                    auto old = copy.at(j);
                    std::stringstream ss(old);
                    std::string add;
                    std::getline(ss, add, ' ');
                    add = "";
                    std::getline(ss, add, ' ');
                    copy.at(j) = target + " " + add;
                    auto [accum, safe] = runProgram(copy);
                    if (safe) {
                        std::cout << "Part 2: " << accum << std::endl;
                        return;
                    }
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
