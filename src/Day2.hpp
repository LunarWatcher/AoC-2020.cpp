#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "util/Loader.hpp"
#include <regex>

namespace aoc {

class Day2 {
private:
    std::vector<std::string> input = aoc::loadFile("day2.txt");
    std::vector<std::tuple<std::pair<int, int>, char, std::string>> parsed;
public:

    Day2() {
        std::regex matcher("(\\d+)-(\\d+) ([a-z]): (.*)");
        for (auto& line : input) {
            std::smatch match;
            if (!std::regex_search(line, match, matcher)) {
                std::cerr << "malformed line: " << line << std::endl;
                throw "abort";
            }
            auto from = std::stoi(match[1]);
            auto to = std::stoi(match[2]);
            const char chr = match[3].str()[0];
            auto password = match[4];

            parsed.push_back(std::make_tuple<std::pair<int, int>, char, std::string>(std::make_pair(from, to), (char) chr, password));
        }
    }

    int part1() {
        int valid = 0;
        for (auto& [fromTo, chr, password] : parsed) {
            auto& [from, to] = fromTo;
            
            auto found = std::count(password.begin(), password.end(), chr);
            if (found >= from && found <= to) {
                valid += 1;
            }
        }
        return valid;
    }

    int part2() {
        int valid = 0;

        for (auto& [requiredPositions, chr, password] : parsed) {
            auto& [a, b] = requiredPositions;
            auto atA = password.at(a - 1);
            auto atB = password.at(b - 1);
            if (atA != atB && (atA == chr || atB == chr)) {
                valid += 1;
            }

        }
        return valid;
    }

    void run() {
        std::cout << "Part 1: " << part1() << "\n"
            << "Part 2: " << part2() << std::endl;
    }
};

}
