#ifndef LOCK_FREE_DATA_STRUCTURE_UTILS_HPP
#define LOCK_FREE_DATA_STRUCTURE_UTILS_HPP

namespace utils {
    
/*
 * Formula:
 *   (N & (N - 1) == 0)
 * Description:
 *   Given the formula, all power of two integers will always be equal to 0.
 * Example:
 *   N = 4; which is a power of two.
 *    4 & (4 - 1) => 4 & 3
 *    Binary form: 100 & 011 => 0
 *   N = 7; which is NOT a power of two.
 *    7 & (7 - 1) => 7 & 6
 *    Binary form: 111 & 110 => 110 (6)
 */
template <std::size_t N>
concept IsPowerOfTwo = (N != 0) && ((N & (N - 1)) == 0);

} // namespace utils
#endif // LOCK_FREE_DATA_STRUCTURE_UTILS_HPP
