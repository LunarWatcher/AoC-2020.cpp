#include <iostream>

#include "Day1.hpp"
#include "Day2.hpp"
#include "Day3.hpp"
#include "Day4.hpp"

int main(int argc, char* argv[]) {
    switch (argv[1][0]) {
        case '1':
            {
                aoc::Day1{}.run();
            } break;
        case '2':
            {
                aoc::Day2{}.run();
            } break;
        case '3':
            {
                aoc::Day3{}.run();
            } break;
        case '4':
            {
                aoc::Day4{}.run();
            } break;
    }
}
