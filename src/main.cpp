#include <iostream>

#include "Day1.hpp"
#include "Day2.hpp"
#include "Day3.hpp"
#include "Day4.hpp"
#include "Day5.hpp"
#include "Day6.hpp"
#include "Day7.hpp"
#include "Day8.hpp"

int main(int argc, char* argv[]) {
    switch (argv[1][0]) {
    case '1': {
        aoc::Day1{}.run();
    } break;
    case '2': {
        aoc::Day2{}.run();
    } break;
    case '3': {
        aoc::Day3{}.run();
    } break;
    case '4': {
        aoc::Day4{}.run();
    } break;
    case '5': {
        aoc::Day5{}.run();
    } break;
    case '6': {
        aoc::Day6{}.run();
    }
    case '7': {
        aoc::Day7{}.run();
    }
    case '8': {
        aoc::Day8{}.run();
    }
    }
}
