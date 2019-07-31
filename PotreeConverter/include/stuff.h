
#ifndef STUFF_H
#define STUFF_H

#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <experimental/filesystem>

#include "AABB.h"
#include "GridCell.h"
#include "Point.h"
#include "SparseGrid.h"
#include "Vector3.h"

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::map;
using std::max;
using std::min;
using std::ofstream;
using std::ostream;
using std::string;
using std::vector;

namespace fs = std::experimental::filesystem;

namespace Potree {

AABB
readAABB(string fIn, int numPoints);

AABB
readAABB(string fIn);

/**
 *   y
 *   |-z
 *   |/
 *   O----x
 *
 *   3----7
 *  /|   /|
 * 2----6 |
 * | 1--|-5
 * |/   |/
 * 0----4
 *
 */
AABB
childAABB(const AABB& aabb, const int& index);

/**
 *   y
 *   |-z
 *   |/
 *   O----x
 *
 *   3----7
 *  /|   /|
 * 2----6 |
 * | 1--|-5
 * |/   |/
 * 0----4
 *
 */
int
nodeIndex(const AABB& aabb, const Vector3<double>& pointPosition);

/**
 * from
 * http://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c
 */
long
filesize(string filename);

/**
 * from
 * http://stackoverflow.com/questions/874134/find-if-string-endswith-another-string-in-c
 */
bool
endsWith(std::string const& fullString, std::string const& ending);

/**
 * see
 * http://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case
 */
string
toUpper(string str);

bool
copyDir(fs::path source, fs::path destination);

float
psign(float value);

// see
// https://stackoverflow.com/questions/23943728/case-insensitive-standard-string-comparison-in-c
bool
icompare_pred(unsigned char a, unsigned char b);

// see
// https://stackoverflow.com/questions/23943728/case-insensitive-standard-string-comparison-in-c
bool
icompare(string const& a, string const& b);

bool
endsWith(const string& str, const string& suffix);

bool
iEndsWith(const string& str, const string& suffix);

vector<string>
split(string str, vector<char> delimiters);

vector<string>
split(string str, char delimiter);

// see
// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
string
ltrim(string s);

// see
// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
string
rtrim(string s);

// see
// https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
string
trim(string s);

/// <summary>
/// Converts 16-bit intensity values to greyscale using logarithmization. This
/// compresses the dynamic range so that the visualization is more pleasing
/// (otherwise low intensity values would be very dark)
/// </summary>
Potree::Vector3<uint8_t>
intensityToRGB_Log(uint16_t intensity);

} // namespace Potree

/// <summary>
/// Aligns the given number using the given alignment
/// </summary>
template<typename Number>
constexpr Number
align(Number value, Number alignment)
{
  if (!value)
    return value;
  if (!alignment)
    return value;

  const auto remainder = value % alignment;
  if (!remainder)
    return value;
  return value + alignment - remainder;
}

template<typename T>
constexpr size_t
vector_byte_size(const std::vector<T>& vec)
{
  return vec.size() * sizeof(T);
}

std::vector<fs::path>
get_all_files_in_directory(const std::string& dir_path);

template<typename Iter>
std::vector<std::pair<Iter, Iter>>
split_range_into_chunks(size_t num_chunks, Iter begin, Iter end)
{
  const auto num_elements = std::distance(begin, end);
  assert(num_elements >= num_chunks);
  const auto chunk_size = num_elements / num_chunks;
  std::vector<std::pair<Iter, Iter>> chunks;
  chunks.reserve(num_chunks);
  for (size_t idx = 0; idx < num_chunks - 1; ++idx) {
    chunks.push_back(std::make_pair(begin + (idx * chunk_size), begin + (idx + 1) * chunk_size));
  }
  chunks.push_back(std::make_pair(begin + (num_chunks - 1) * chunk_size, end));
  return chunks;
}

template<typename... Args>
std::string
concat(const Args&... args)
{
  std::stringstream ss;
  (ss << ... << args);
  return ss.str();
}

#endif
