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

using rule_t = std::pair<size_t, size_t>;
using rules_t = std::vector<rule_t>;
using edit_t = std::vector<size_t>;
using edits_t = std::vector<edit_t>;

struct input_t {
  input_t(std::string& text) {
    std::regex pattern(R"(((\d+)\|(\d+))|(\d+(?:,\d+)*))");
    std::sregex_iterator reg_begin(text.begin(), text.end(), pattern);
    std::sregex_iterator reg_end;

    for (auto it = reg_begin; it != reg_end; ++it) {
      const std::smatch& match = *it;

      if (match[1].matched) {
        rule_t rule{std::stoi(match[2]), std::stoi(match[3])};
        rules.push_back(rule);
      } else if (match[4].matched) {
        std::stringstream ss(match[4].str());
        edit_t edit;
        std::string page;

        while (std::getline(ss, page, ',')) {
          edit.push_back(std::stoi(page));
        }

        edits.push_back(edit);
      }
    }
  }

  rules_t rules;
  edits_t edits;
};

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

  input_t input(text);

  return input;
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
