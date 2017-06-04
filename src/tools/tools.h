#ifndef __TOOLS_H
#define __TOOLS_H

#include <cstddef>

namespace containers {
namespace tools {

/**
 * Returns the exponent of smallest multiple of ``base`` that is greater than
 * ``n``
 *
 * @param n number of elements needed memory capacity
 * @param base the base of the capacity (default is 2)
 *
 * @return the exponent required to make ``pow(base, X) > n`` true
 */
long capacity_for_size(std::size_t n, long base=2);
} // namespace tools
} // namespace containers
#endif // __TOOLS_H
