#ifndef LOCK_FREE_DATA_STRUCTURE_UTILS_HPP
#define LOCK_FREE_DATA_STRUCTURE_UTILS_HPP

namespace utils {
    
template <std::size_t N>
concept IsPowerOfTwo = (N != 0) && ((N & (N - 1)) == 0);

} // namespace utils
#endif // LOCK_FREE_DATA_STRUCTURE_UTILS_HPP
