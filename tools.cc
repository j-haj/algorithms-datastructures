#include "tools.h"

#include <cmath>

namespace containers {
namespace tools {

long capacity_for_size(size_t n, long base=2) {
  return long(std::log(n)/std::log(base)) + 1;
}
