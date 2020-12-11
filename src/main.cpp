#include <iostream>

#include "Day1.hpp"
#include "Day2.hpp"
#include "Day3.hpp"
#include "Day4.hpp"
#include "Day5.hpp"
#include "Day6.hpp"
#include "Day7.hpp"
#include "Day8.hpp"
#include "Day9.hpp"
#include "Day10.hpp"
#include "Day11.hpp"

int main(int argc, char* argv[]) {
    std::string input(argv[1]);
    if (input == "1") {
        aoc::Day1{}.run();
    } else if (input == "2") {
        aoc::Day2{}.run();
    } else if (input == "3") {
        aoc::Day3{}.run();
    } else if (input == "4") {
        aoc::Day4{}.run();
    } else if (input == "5") {
        aoc::Day5{}.run();
    } else if (input == "6") {
        aoc::Day6{}.run();
    } else if (input == "7") {
        aoc::Day7{}.run();
    } else if (input == "8") {
        aoc::Day8{}.run();
    } else if (input == "9") {
        aoc::Day9{}.run();
    } else if (input == "10") {
        aoc::Day10{}.run();
    } else if (input == "11") {
        aoc::Day11{}.run();
    }

}
