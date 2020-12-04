#pragma once

#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

#include "util/Loader.hpp"

namespace aoc {

class Day4 {
private:
    std::vector<std::string> rawData = loadFile("day4.txt");
    std::vector<std::map<std::string, std::string>> passports;
    std::vector<std::string> legalColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

public:
    Day4() {
        std::map<std::string, std::string> passport;
        for (auto& line : rawData) {
            if (line == "") {
                passports.push_back(passport);
                passport.clear();
                continue;
            }

            std::stringstream ss(line);
            std::string tmp;
            while (std::getline(ss, tmp, ' ')) {
                std::string key;
                size_t idx = tmp.find(":");
                key = tmp.substr(0, idx);
                passport[key] = tmp.substr(idx + 1);
            }
        }
        passports.push_back(passport);
    }

    int part1() {
        int valid = 0;
        for (auto& passport : passports) {
            if (passport.size() == 8 || (passport.size() == 7 && !passport.contains("cid"))) {
                ++valid;
            }
        }
        return valid;
    }

    int part2() {
        int valid = 0;

        for (auto& passport : passports) {
            if (passport.size() == 8 || (passport.size() == 7 && !passport.contains("cid"))) {
                bool invalid = false;
                for (auto& [key, value] : passport) {
                    if (key == "cid") continue;
                    try {
                        if (key == "byr") {
                            int year = std::stoi(value);
                            if (year < 1920 || year > 2002) {
                                invalid = true;
                                break;
                            }
                        } else if (key == "iyr") {
                            int year = std::stoi(value);
                            if (year < 2010 || year > 2020) {
                                invalid = true;
                                break;
                            }
                        } else if (key == "eyr") {
                            int year = std::stoi(value);
                            if (year < 2020 || year > 2030) {
                                invalid = true;
                                break;
                            }
                        } else if (key == "hgt") {

                            auto inches = value.ends_with("in");
                            auto cm = value.ends_with("cm");

                            auto num = std::stoi(value);
                            if ((!inches && !cm) ||
                                    ((cm && (num < 150 || num > 193)) || (inches && (num < 59 || num > 76)))) {
                                invalid = true;
                                break;
                            }
                        } else if (key == "hcl") {

                            if (value.at(0) != '#' || value.size() != 7) {
                                invalid = true;
                                break;
                            }
                            std::stoi(value.substr(1), nullptr, 16);
                        } else if (key == "ecl") {
                            if (std::find(legalColors.begin(), legalColors.end(), value) == legalColors.end()) {

                                invalid = true;
                                break;
                            }
                        } else if (key == "pid") {
                            if (value.size() != 9) {
                                invalid = true;
                                break;
                            }
                            std::stoi(value);
                        }
                    } catch (...) {
                        invalid = true;
                        break;
                    }
                }
                if (!invalid) {
                    ++valid;
                }
            }
        }
        return valid;
    }
    void run() {
        std::cout << "Part 1: " << part1() << "\n"
                  << "Part 2: " << part2() << std::endl;
    }
};

} // namespace aoc
