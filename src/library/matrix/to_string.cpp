#include "Matrix.hpp"

namespace arithmetica {
std::string Matrix::to_string() const {
  std::string ans = "{";
  for (std::size_t i = 0; i < m.size(); ++i) {
    ans += "{";
    for (std::size_t j = 0; j < m[i].size(); ++j) {
      ans += m[i][j].to_string();
      if (j != m[i].size() - 1) {
        ans += ", ";
      }
    }
    ans += "}";
    if (i != m.size() - 1) {
      ans += ", ";
    }
  }
  ans += "}";
  return ans;
}

std::string Matrix::to_pretty_string() const {
  if (m.empty()) {
    return "";
  }

  // get the max lengths of each row
  std::vector<size_t> max_len;
  for (size_t i = 0; i < m[0].size(); i++) {
    max_len.push_back(0);
    for (size_t j = 0; j < m.size(); j++) {
      max_len[i] = std::max(max_len[i], m[j][i].to_string().length());
    }
  }

  // start making table
  std::string bar = "┌-";
  for (auto &i : max_len) {
    bar += std::string(i + 2, ' ') + " ";
  }
  bar.pop_back();
  bar.pop_back();
  bar.pop_back();
  bar += "-┐";
  std::string answer = bar;
  for (size_t i = 0; i < m.size(); i++) {
    answer += "\n|";
    for (size_t j = 0; j < m[i].size(); j++) {
      answer += " " + m[i][j].to_string();
      if (max_len[j] - m[i][j].to_string().length() > 0) {
        answer += std::string(max_len[j] - m[i][j].to_string().length(), ' ');
      }
      answer += " ";
      if (j != m[i].size() - 1) {
        answer += " ";
      } else {
        answer += "|";
      }
    }
  }
  std::string bottom_bar = "└-";
  for (auto &i : max_len) {
    bottom_bar += std::string(i + 2, ' ') + " ";
  }
  bottom_bar.pop_back();
  bottom_bar.pop_back();
  bottom_bar.pop_back();
  bottom_bar += "-┘";
  answer += "\n" + bottom_bar;

  return answer;
}
} // namespace arithmetica