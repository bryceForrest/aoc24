#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <utility>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdint>

using input_t = std::vector<std::string>;

input_t parse(std::istream& in);
int64_t part1(std::istream& in);
int64_t part2(std::istream& in);

int main(int argc, char* argv[]) {
    std::string part = argc > 1 ? argv[1] : "1";
    std::string path = argc > 2 && *argv[2] ? argv[2] : "sample_input_part_" + part + ".txt";

    std::ifstream in(path);
    if (!in) {
        std::cerr << "Could not open " << path << "\n";
        return 1;
    }

    if (part == "1") {
        std::cout << "Part 1: " << part1(in) << "\n";
    } else if (part == "2") {
        std::cout << "Part 2: " << part2(in) << "\n";
    } else {
        std::cerr << "Part must be 1 or 2\n";
        return 1;
    }

    return 0;
}

input_t parse(std::istream& in) {
    std::string line;
    input_t lines;

    while (std::getline(in, line)) {
        lines.push_back(line);
    }

    return lines;
}

int64_t part1(std::istream& in) {
    input_t input = parse(in);
    int64_t result = 0;

    return result;
}

int64_t part2(std::istream& in) {
    input_t input = parse(in);
    int64_t result = 0;

    return result;
}
