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

using coord = std::pair<int, int>;

struct input_t {
  input_t(std::string text) {
    std::stringstream ss(text);
    std::string line;
    const std::string position_ch = "^v<>";
    int i = 0;

    while (std::getline(ss, line)) {
      for (int j = 0; j < line.size(); j++) {
        if (position_ch.find(line[j]) != std::string::npos) {
          pos = {i, j};
          direction_ = line[j];
        } else if (line[j] == '#') {
          map.insert(coord{i, j});
        }
      }

      i++;
    }

    n = i;
    m = line.size();
  }

  coord direction() { return direction_map_.at(direction_); }

  bool off_map(coord x) {
    return (x.first < 0 || x.first >= n || x.second < 0 || x.second >= m);
  }

  bool obstruction(coord x) { return static_cast<bool>(map.count(x)); }
  void change_direction() {
    if (direction_ == '^') {
      direction_ = '>';
    } else if (direction_ == '>') {
      direction_ = 'v';
    } else if (direction_ == 'v') {
      direction_ = '<';
    } else {  // if (direction_ == '<')
      direction_ = '^';
    }
  }

  std::set<coord> map;
  coord pos;
  int n;
  int m;
  char direction_;
  const std::unordered_map<char, coord> direction_map_{
      {'^', {-1, 0}}, {'v', {1, 0}}, {'<', {0, -1}}, {'>', {0, 1}}};
};

input_t parse(std::istream& in);
bool traverse(input_t& input, std::set<coord>& visited);
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

bool traverse(input_t& input, std::set<coord>& visited) {
  coord dir = input.direction();
  coord next_pos{input.pos.first + dir.first, input.pos.second + dir.second};
  bool off_map = input.off_map(next_pos);

  if (!off_map) {
    if (input.obstruction(next_pos)) {
      input.change_direction();
    } else {
      input.pos = next_pos;
    }
  }

  visited.insert(input.pos);

  return off_map;
}

int64_t part1(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;
  std::set<coord> visited;

  while (!traverse(input, visited)) {
    // pass
  }

  return visited.size();
}

int64_t part2(std::istream& in) {
  input_t input = parse(in);
  int64_t result = 0;

  return result;
}
