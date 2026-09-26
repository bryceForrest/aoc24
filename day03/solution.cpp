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
  std::istreambuf_iterator<char> stream_begin{in};
  std::istreambuf_iterator<char> stream_end;
  std::string text{stream_begin, stream_end};

  return text;
}

int64_t part1(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;
  std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
  std::sregex_iterator reg_begin(input.begin(), input.end(), pattern);
  std::sregex_iterator reg_end;

  for (auto it = reg_begin; it != reg_end; ++it) {
    const std::smatch& match = *it;
    result += std::stoi(match[1]) * std::stoi(match[2]);
  }

  return result;
}

int64_t part2(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;
  std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|(don\'t\(\))|(do\(\)))");
  std::sregex_iterator reg_begin(input.begin(), input.end(), pattern);
  std::sregex_iterator reg_end;
  bool do_flag = true;

  for (auto it = reg_begin; it != reg_end; ++it) {
    // index 0 is entire match
    // index 1 and 2 are nums 1 and 2
    // index 3 is "don't", index 4 is "do"
    const std::smatch& match = *it;

    if (match[3].str() == "don't()") {
      do_flag = false;
    } else if (match[4].str() == "do()") {
      do_flag = true;
    } else {
      // it must be a mul(...) match
      result += static_cast<int>(do_flag) *
                (std::stoi(match[1]) * std::stoi(match[2]));
    }
  }

  return result;
}
