#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <sstream>

namespace aoc {

int sastoi(const std::string& input) { return std::stoi(input); }
long long sastoll(const std::string& input) { return std::stoll(input); }

std::vector<int> convertStringToIntVec(const std::string& input, char delimiter) {
    std::vector<int> vec;
    std::stringstream ss(input);
    std::string tmp;
    while (std::getline(ss, tmp, ',')) {
        vec.push_back(std::stoi(tmp));
    }
    return vec;
}

std::vector<std::string> loadFile(const std::string& filename) {
    std::ifstream stream("input/" + filename);
    if (!stream) {
        throw "File not found: " + filename;
    }
    std::vector<std::string> str;
    std::string tmp;

    while (std::getline(stream, tmp)) {
        str.push_back(tmp);
    }
    return str;
}

template <typename T>
std::vector<T> loadType(const std::string& filename, std::function<T(const std::string&)> converter) {
    auto rawFile = loadFile(filename); 
    std::vector<T> vec;

    for (auto& tmp : rawFile) {
        vec.push_back(converter(tmp));
    }
    return vec;
}

}
