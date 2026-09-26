#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using input_t = std::vector<std::vector<int>>;

input_t parse(std::istream& in);
int sign(int x);
bool is_safe(int diff, int prev_diff);
int64_t part1(std::istream& in);
bool part1_helper(const std::vector<int>& row);
int64_t part2(std::istream& in);
bool part2_helper(const std::vector<int>& row, const size_t& index,
                  const int& prev_value, const int& prev_diff,
                  const bool& is_counterfactual);

int main(int argc, char* argv[]) {
  std::string part = argc > 1 ? argv[1] : "1";
  std::string path =
      argc > 2 && *argv[2] ? argv[2] : ("sample_input_part_" + part + ".txt");

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
  std::string token;
  input_t grid;

  while (std::getline(in, line)) {
    std::vector<int> row;
    std::stringstream ss(line);

    while (ss >> token) {
      row.push_back(std::stoi(token));
    }

    grid.push_back(row);
  }

  return grid;
}

int sign(int x) {
  // if x is positive, (1) - (0) = 1
  // if x is negative, (0) - (1) = -1
  // else              (0) - (0) = 0

  return (0 < x) - (x < 0);
}

bool is_safe(int diff, int prev_diff) {
  int abs_diff = std::abs(diff);
  bool unsafe_sign = (prev_diff != 0) && (sign(diff) != sign(prev_diff));
  bool unsafe_diff = abs_diff < 1 || abs_diff > 3;

  return !(unsafe_sign || unsafe_diff);
}

int64_t part1(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;

  for (size_t i = 0; i < input.size(); i++) {
    std::vector<int> row = input[i];
    bool row_valid = part1_helper(row);

    if (row_valid) {
      result++;
    }
  }

  return result;
}

bool part1_helper(const std::vector<int>& row) {
  bool row_valid = true;
  int prev_diff = 0;

  for (size_t i = 1; i < row.size() && row_valid; i++) {
    int diff = row[i] - row[i - 1];
    int abs_diff = std::abs(diff);
    bool safe = is_safe(diff, prev_diff);

    row_valid = safe;
    prev_diff = diff;
  }

  return row_valid;
}

int64_t part2(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;

  for (size_t i = 0; i < input.size(); i++) {
    std::vector<int> row = input[i];
    bool row_valid = part2_helper(row, 0, -1, 0, false);

    if (row_valid) {
      result++;
    }
  }

  return result;
}

bool part2_helper(const std::vector<int>& row, const size_t& index,
                  const int& prev_index, const int& prev_diff,
                  const bool& is_counterfactual) {
  // returns if row is valid, so NOT unsafe
  if (index == row.size()) {
    // if we got to the end, it's not unsafe (IS valid)
    return true;
  }

  // pretend row[index] isn't here, only if we haven't before
  if (!is_counterfactual &&
      part2_helper(row, index + 1, prev_index, prev_diff, true)) {
    return true;
  }

  if (prev_index < 0) {
    // nothing to compare against yet
    return part2_helper(row, index + 1, index, 0, is_counterfactual);
  }

  int value = row[index];
  int prev_value = row[prev_index];
  int diff = value - prev_value;

  if (!is_safe(diff, prev_diff)) {
    return false;
  }

  return part2_helper(row, index + 1, index, diff, is_counterfactual);
  ;
}
