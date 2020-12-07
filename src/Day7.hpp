#pragma once

#include "util/Loader.hpp"
#include <iostream>
#include <map>
#include <pstl/pstl_config.h>
#include <queue>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

namespace aoc {

class Day7 {
private:
    std::vector<std::string> rawData = loadFile("day7.txt");
    std::map<std::string, std::vector<std::pair<int, std::string>>> reverseTree;

public:
    void A() {
        std::regex splitRegex("( bags contain |, )");
        int canContainShiny = 0;

        for (const std::string& rawLine : rawData) { // {{{
            auto line = rawLine.substr(0, rawLine.size() - 1);

            std::sregex_token_iterator it(line.begin(), line.end(), splitRegex, -1);
            std::sregex_token_iterator end;
            std::string rootBag;
            std::vector<std::string> contained;

            for (; it != end; ++it) {
                if (rootBag == "") {
                    rootBag = *it;
                    continue;
                }
                contained.push_back(*it);
            }

            if (line.find("no other bags") == std::string::npos) {
                for (auto& rawBag : contained) {
                    int backOffset = 4;
                    if (rawBag.find("bags") != std::string::npos)
                        ++backOffset;
                    std::string parsedBagName = rawBag.substr(2, rawBag.size() - 2 - backOffset);
                    reverseTree[parsedBagName].push_back({rawBag.at(0) - '0', rootBag});
                }
            }
        } // }}}

        std::string root = "shiny gold";
        std::queue<std::string> queue;

        std::vector<std::string> exhausted = {"shiny gold"};

        do {
            auto& tmp = reverseTree[root];
            if (tmp.size()) {
                for (auto& [_, bag] : tmp) {
                    if (std::find(exhausted.begin(), exhausted.end(), bag) != exhausted.end())
                        continue;
                    queue.push(bag);
                    exhausted.push_back(bag);
                }
            }
            ++canContainShiny;
            root = queue.front();
            queue.pop();
        } while (!queue.empty());

        std::cout << "Part 1: " << canContainShiny << std::endl;

    }

    int recB(std::string& root) {
        if (!reverseTree.contains(root)) return 0;
        auto& children = reverseTree.at(root);
        int sum = 0;

        for (auto& child : children) {
            sum += child.first;
            sum += child.first * recB(child.second);
        }
        return sum;
    }

    void B() {
        int count = 0;
        throw std::runtime_error("FIXME");
        std::string root = "shiny gold";
        count = recB(root);
        std::cout << "Part 2: " << count << std::endl;
    }

    void run() {
        A();
        B();
    }
};

} // namespace aoc
