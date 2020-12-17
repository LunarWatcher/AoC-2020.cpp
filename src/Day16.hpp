#pragma once

#include "util/Loader.hpp"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

namespace aoc {

class Day16 {
private:
    std::vector<std::string> rawInput = loadFile("day16.txt");
    std::vector<std::vector<std::pair<int, int>>> restrictions;
    std::vector<int> myTicket;
    std::vector<std::vector<int>> nearbyTickets;
    std::vector<std::vector<int>> valid;

public:
    Day16() {

        int state = 0;
        for (auto& line : rawInput) {
            if (line == "") {
                ++state;
            } else {
                if (line == "your ticket:")
                    continue;
                if (line == "nearby tickets:")
                    continue;

                switch (state) {
                case 0: {
                    std::smatch match;
                    std::regex_search(line, match, std::regex("(\\d+)-(\\d+) or (\\d+)-(\\d+)"));
                    restrictions.push_back({std::pair<int, int>(std::stoi(match[1]), std::stoi(match[2])),
                            std::pair<int, int>(std::stoi(match[3]), std::stoi(match[4]))});
                } break;
                case 1: {
                    this->myTicket = convertStringToIntVec(line, ',');
                } break;
                case 2: {
                    this->nearbyTickets.push_back(convertStringToIntVec(line, ','));
                } break;
                }
            }
        }
    }

    void part1() {
        int invalid = 0;
        for (auto& ticket : nearbyTickets) {
            for (auto& value : ticket) {
                for (auto& restriction : restrictions) {
                    for (auto& [from, to] : restriction) {
                        if (value >= from && value <= to) {
                            goto abrt;
                        }
                    }
                }

                {
                    invalid += value;
                    goto abrt2;
                }
            abrt:
                continue;
            }
            valid.push_back(ticket);
        abrt2:;
        }

        std::cout << "Part 1: " << invalid << std::endl;
    }

    void part2() {

        std::map<int, std::vector<int>> restrIdxToPos;

        for (size_t i = 0; i < restrictions.size(); ++i) {
            for (size_t offset = 0; offset < restrictions.size(); ++offset) {
                bool containsInvalid = false;
                for (auto& ticket : this->valid) {
                    auto field = ticket.at(offset);
                    bool valid = false;
                    for (auto& [from, to] : restrictions.at(i)) {
                        if (field >= from && field <= to) {
                            valid = true;
                            break;
                        }
                    }
                    if (!valid) {
                        containsInvalid = true;
                        break;
                    }
                }
                if (!containsInvalid) {
                    restrIdxToPos[i].push_back(offset);
                }
            }
        }


        for (auto& [idx, vec] : restrIdxToPos) {
            std::cout << idx << (idx < 10 ? " " : "") << " -> ";

            for (int i = 0; i < 20; i++) {
                if (std::find(vec.begin(), vec.end(), i) == vec.end()) {
                    std::cout << "-- ";
                } else

                    std::cout << i << (i < 10 ? " " : "") << " ";
            }
            std::cout << "\n";
        }

        while (true) {
            bool dirty = false;
            for (auto& [idx, vec] : restrIdxToPos) {
                if (vec.size() == 1) {
                    for (auto& [_, vec2] : restrIdxToPos) {
                        if (vec2.size() == 1) continue;
                        std::erase(vec2, vec.at(0));
                    }
                } else dirty = true;
            }
            if (!dirty) {
                break;
            }
        }
        std::cout << "-----------" << std::endl;
        for (auto& [idx, vec] : restrIdxToPos) {
            std::cout << idx << (idx < 10 ? " " : "") << " -> ";

            for (int i = 0; i < 20; i++) {
                if (std::find(vec.begin(), vec.end(), i) == vec.end()) {
                    std::cout << "-- ";
                } else

                    std::cout << i << (i < 10 ? " " : "") << " ";
            }
            std::cout << "\n";
        }
        size_t prod = 1;
        for (int i = 0; i < 6; i++)
            prod *= this->myTicket.at(restrIdxToPos.at(i).at(0));
        std::cout << "Part 2: " << prod << std::endl;
    }

    void run() {
        part1();
        part2();
    }
};

} // namespace aoc
