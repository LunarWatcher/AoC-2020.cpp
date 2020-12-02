#include <iostream>

#include "Day1.hpp"
#include "Day2.hpp"

int main(int argc, char* argv[]) {
    switch (argv[1][0]) {
        case '1':
            {
                aoc::Day1{}.run();
            }
            break;
        case '2':
            {
                aoc::Day2{}.run();
            }
            break;
    }
}
