#pragma once

#include "util/Loader.hpp"
#include <bitset>
#include <iostream>
#include <math.h>
#include <numeric>
#include <regex>

namespace aoc {

class Day14 {
private:
    std::vector<std::string> rawData = loadFile("day14.txt");
    std::map<std::string, std::vector<std::pair<long long, std::bitset<36>>>> data;

    std::bitset<36> convert(const std::string& binary) {
        return std::bitset<36>(std::stoll(binary, nullptr, 2));
    }

public:
    Day14() {
        const std::regex regex(R"DEL(mem\[(\d+)\] = (\d+))DEL");
        std::string mask;
        std::vector<std::pair<long long, std::bitset<36>>> data;
        for (auto& line : rawData) {
            if (line.starts_with("mask")) {
                if (data.size() != 0) {
                    this->data[mask] = data;
                    data.clear();
                    mask = "";
                }
                mask = line.substr(7);
            } else {
                
                std::smatch match;
                std::regex_search(line, match, regex);

                data.push_back(std::pair<long long, std::bitset<36>>(
                        std::stoll(match[1]), std::bitset<36>(std::stoll(match[2]))));
            }
        }


        this->data[mask] = data;
        
    }

    void part1() {
        std::map<long long, std::bitset<36>> executed;
        for (auto& [mask, nums] : this->data) {
            std::string orMask = std::regex_replace(mask, std::regex("X"), "0");
            std::string andMask = std::regex_replace(mask, std::regex("X"), "1");

            for (auto& [addr, num] : nums) {
                /**
                 * I have no idea why this doesn't work. It should work.
                 * It passes the test case, but still fails on the real input. Can't find the reason why.
                 * I've checked the return types (although with the answer being in the range of 1e13,
                 * that shouldn't be a problem), sanity-checked the logic... I can't find whatever's wrong.
                 *
                 * Might've been able to find it if I had more tests, but with just one test case and bitwise
                 * operations being something I generally don't understand, iDunno.
                 * I tried. I'll just use one of my stars from last year to get the vacation :')
                 */ 
                auto cacheNum = num;
                cacheNum = (cacheNum | convert(orMask)) & convert(andMask);
                executed[addr] = cacheNum;
            }
        }
        size_t ans = std::accumulate(executed.begin(), executed.end(), size_t(0), [](const auto& prev, const auto& bitset) {
                    return prev + bitset.second.to_ullong();
                });
        std::cout << "Part 1: " << ans << std::endl;
    }

    void run() {
        throw std::runtime_error("Day 14 doesn't work.");
        part1();
    }
};

} // namespace aoc
