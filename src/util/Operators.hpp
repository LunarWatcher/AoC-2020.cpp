#pragma once

namespace aoc {

namespace operators {
// define a dummy object that is the name of the operator
const struct mod_ {
} modulo;

// Define a proxy to act as a temporary object between the two.
// Holds a reference to prevent unnecessary copying
template <typename T>
struct ModProxy {
    const T& t;
    ModProxy(const T& t) : t(t) {}
};

// Define operator< to make the left side valid
template <typename T>
ModProxy<T> operator<(const T& lhs, const mod_& rhs) {
    return ModProxy<T>(lhs);
}

// Define operator> to make the right side valid
template <typename T>
T operator>(const ModProxy<T>& lhs, const T& rhs) {
    // and this is why this operator exists.
    // Normal modulo doesn't account for negative numbers in C++.
    // https://stackoverflow.com/q/38251229
    // It's ridiculous, and has caused me a bit of pain when dealing with
    // day 12 and 13 (because I expect something I don't get), sooooooooo
    // I made an operator that does this by default. Problem solved \o/
    return ((lhs.t % rhs) + rhs) % rhs;
}

} // namespace operators
// define a macro that's prettier than using <modulo> in the code
#define mod <operators::modulo>
// ... and `x mod y` is now valid.
} // namespace aoc
