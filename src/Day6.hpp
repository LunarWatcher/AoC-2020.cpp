#include "util/Loader.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace aoc {

class Day6 {
private:
    std::vector<std::string> rawData = loadFile("day6.txt");
    int part2Ans;
public:
    int part1() {

        int count = 0;

        std::map<char, int> questions;
        int peeps = 0;
        for (int i = 0; i < rawData.size(); ++i) {
            auto& line = rawData.at(i);

            if (line.size()) {
                peeps++;
                for (auto& character : line) {
                    questions[character] = (questions.contains(character) ? questions[character] : 0) + 1; 
                }
            }
            if (line == "" || i == rawData.size() - 1) {
                count += questions.size();
                for (auto& [question, cnt] : questions) {
                    if (cnt == peeps) {
                        ++part2Ans;
                    }
                }
                
                peeps = 0;
                questions.clear();
            }
        }

        return count;
    }

    int part2() {
        return part2Ans;
    }

    void run() {
        std::cout << "Part 1: " << part1() << "\nPart 2: " << part2() << std::endl;
    }
};

} // namespace aoc

