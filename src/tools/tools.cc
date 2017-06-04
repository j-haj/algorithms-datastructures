#include "tools/tools.h"

#include <cmath>

namespace containers {
namespace tools {

long capacity_for_size(std::size_t n, long base) {
  return long(std::log(n)/std::log(base)) + 1;
}

} // namespace tools
} // namespace containers
