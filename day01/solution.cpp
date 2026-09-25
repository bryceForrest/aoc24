#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using lists_t = std::pair<std::vector<int>, std::vector<int>>;

lists_t parse(std::istream& in);
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

lists_t parse(std::istream& in) {
  std::string left_token;
  std::string right_token;
  lists_t lists;

  while (in >> left_token >> right_token) {
    lists.first.push_back(std::stoi(left_token));
    lists.second.push_back(std::stoi(right_token));
  }

  return lists;
}

int64_t part1(std::istream& in) {
  lists_t lists = parse(in);
  int64_t distance = 0;

  std::sort(lists.first.begin(), lists.first.end());
  std::sort(lists.second.begin(), lists.second.end());

  for (size_t i = 0; i < lists.first.size(); i++) {
    distance += std::abs(lists.first[i] - lists.second[i]);
  }

  return distance;
}

int64_t part2(std::istream& in) {
  lists_t lists = parse(in);
  int64_t similarity = 0;
  std::unordered_map<int, int> frequency_map;

  for (auto& val : lists.second) {
    frequency_map[val]++;
  }

  for (auto& val : lists.first) {
    similarity += static_cast<int64_t>(val) * frequency_map[val];
  }

  return similarity;
}
