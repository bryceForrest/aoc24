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

using row_t = std::vector<char>;
using input_t = std::vector<row_t>;
using count_t = std::vector<std::vector<size_t>>;

input_t parse(std::istream& in);
char safe_index(const input_t& input, const int& i, const int& j);
int64_t traverse(const input_t& input, const size_t& i, const size_t& j);
int64_t part1(std::istream& in);
void traverse_diag(const input_t& input, count_t& count, const size_t& i,
                   const size_t& j);
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
  std::string line;
  input_t rows;

  while (std::getline(in, line)) {
    row_t row;
    for (auto& ch : line) {
      row.push_back(ch);
    }

    rows.push_back(row);
  }

  return rows;
}

char safe_index(const input_t& input, const int& i, const int& j) {
  size_t n = input.size();
  size_t m = input[0].size();
  char ch;

  if (i < 0 || i >= n || j < 0 || j >= m) {
    ch = '\0';
  } else {
    ch = input[i][j];
  }

  return ch;
}

int64_t traverse(const input_t& input, const size_t& i, const size_t& j) {
  const std::string target = "XMAS";
  const int directions[8][2] = {{0, 1},  {1, 1},   {1, 0},  {1, -1},
                                {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
  int64_t found = 0;

  for (auto& direction : directions) {
    bool possible = true;
    std::string word;

    for (int k = 0; k < target.size() && possible; k++) {
      int step[2] = {direction[0] * k, direction[1] * k};
      word += safe_index(input, static_cast<int>(i) + step[0],
                         static_cast<int>(j) + step[1]);
      possible = word == target.substr(0, word.size());
    }

    found += static_cast<int>(word == target);
  }

  return found;
}

int64_t part1(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;

  for (size_t i = 0; i < input.size(); i++) {
    row_t row = input[i];
    for (size_t j = 0; j < row.size(); j++) {
      result += traverse(input, i, j);
    }
  }

  return result;
}

void traverse_diag(const input_t& input, count_t& count, const size_t& i,
                   const size_t& j) {
  const std::string target = "MAS";
  const int directions[8][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
  int64_t found = 0;

  for (auto& direction : directions) {
    bool possible = true;
    std::string word;

    for (int k = 0; k < target.size() && possible; k++) {
      int step[2] = {direction[0] * k, direction[1] * k};
      word += safe_index(input, static_cast<int>(i) + step[0],
                         static_cast<int>(j) + step[1]);
      possible = word == target.substr(0, word.size());
    }

    if (word == target) {
      // if the word is valid, the indices are valid, so we can bravely add
      // to i and j here without worrying about scampering out of bounds
      count[i + direction[0]][j + direction[1]]++;
    }
  }
}

int64_t part2(std::istream& in) {
  input_t input = parse(in);
  count_t count(input.size(), std::vector<size_t>(input[0].size()));
  int64_t result = 0;
  // we now only need to check diagonal directions
  // I think the easiest thing to do is to just track the center 'A' position
  // of each "MAS" found ... then at the end just see how many of those
  // coordinates are counted twice.
  for (size_t i = 0; i < input.size(); i++) {
    row_t row = input[i];
    for (size_t j = 0; j < row.size(); j++) {
      traverse_diag(input, count, i, j);
    }
  }

  for (auto& row : count) {
    for (auto& elem : row) {
      result += static_cast<int>(elem == 2);
    }
  }

  return result;
}
