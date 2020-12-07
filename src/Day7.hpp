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

public:
    void A() {
        std::map<std::string, std::vector<std::string>> reverseTree;
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
                    reverseTree[parsedBagName].push_back(rootBag);
                }
            }
        } // }}}

        std::string root = "shiny gold";
        std::queue<std::string> queue;

        std::vector<std::string> exhausted = {"shiny gold"};

        do {
            auto& tmp = reverseTree[root];
            if (tmp.size()) {
                for (auto& bag : tmp) {
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

    int recursiveB(const std::string& root, const std::map<std::string, std::vector<std::pair<int, std::string>>>& tree) {
        if (!tree.contains(root)) return 0;
        int sum = 0;

        auto& children = tree.at(root);
        for (auto& child : children) {
            sum += child.first;
            sum += child.first * recursiveB(child.second, tree);
        }
        return sum;
    }

    void B() {
        std::map<std::string, std::vector<std::pair<int, std::string>>> tree;
        std::regex splitRegex("( bags contain |, )");


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
                    tree[rootBag].push_back({rawBag.at(0) - '0', parsedBagName});
                }
            }
        } // }}}

        std::string root = "shiny gold";
        std::cout << "Part 2: " << recursiveB(root, tree) << std::endl;
    }

    void run() {
        A();
        B();
    }
};

} // namespace aoc
