#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

namespace DS {

using std::string;
using std::vector;

class SuffixArray {

  using size_type = string::size_type;

public:
  SuffixArray(const string &s) : s_(s) { build(); }
  SuffixArray(string &&s) : s_(std::move(s)) { build(); }

  string GetSuffix(size_t rank) {
    if (rank > s_.size() || rank == npos)
      return "";
    else
      return s_.substr(sa_[rank]);
  }
  size_t GetLCP(size_t posa, size_t posb);
  size_t Match(const string &s);

public:
  static const int MAX_VAL = 256;
  static const size_t npos = string::npos;

private:
  void build_sa();
  void build_height();
  void build_lcp();

  void build() {
    build_sa();
    build_height();
    build_lcp();
  }

private:
  string s_;
  vector<size_t> sa_;
  vector<size_t> rank_;
  vector<size_t> height_;
  vector<vector<size_t>> sparse_tbl_;
  vector<vector<size_t>> lcp_cache_;
};

}
