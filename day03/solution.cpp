#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using input_t = std::string;

input_t parse(std::istream& in);
int64_t part1(std::istream& in);
int64_t part2(std::istream& in);

int main(int argc, char* argv[]) {
  std::string part = argc > 1 ? argv[1] : "1";
  std::string path =
      argc > 2 && *argv[2] ? argv[2] : "sample_input_part_" + part + ".txt";

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
  std::istreambuf_iterator<char> stream_it{in}, stream_end;
  std::string text{stream_it, stream_end};

  return text;
}

int64_t part1(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;
  std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
  std::sregex_iterator reg_it(input.begin(), input.end(), pattern), reg_end;

  for (; reg_it != reg_end; ++reg_it) {
    const std::smatch& match = *reg_it;
    result += std::stoi(match[1]) * std::stoi(match[2]);
  }

  return result;
}

int64_t part2(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;

  return result;
}
