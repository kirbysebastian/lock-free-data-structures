#ifndef LOCK_FREE_DATA_STRUCTURE_SPSC_BOUNDED_QUEUE_HPP
#define LOCK_FREE_DATA_STRUCTURE_SPSC_BOUNDED_QUEUE_HPP

#include <array>
#include "utils.hpp"

namespace lockfree {

template <typename T, std::size_t N>
requires utils::IsPowerOfTwo<N>
class SPSCBoundedQueue final {
public:

    bool tryPush(T&& value) noexcept {
        if (isFull()) {
            return false;
        }
        m_data[m_headIdx++ & (N - 1)] = std::forward<T>(value);
        return true;
    }

    bool tryPop(T& value) noexcept {
        if (isEmpty()) {
            return false;
        }

        value = m_data[m_tailIdx++ & (N - 1)];
        return true;
    }

    template <class... Args>
    bool emplace(Args&&... args) noexcept {
        return false; // @TODO: Implement me!
    }

    bool isFull() const noexcept {
        return N == (m_headIdx - m_tailIdx);
    }

    bool isEmpty() const noexcept {
        return m_headIdx == m_tailIdx;
    }

    constexpr std::size_t capacity() const noexcept {
        return N;
    }

    std::size_t size() const noexcept {
        return m_headIdx - m_tailIdx;
    }

    // Troubleshoot
    auto getHeadIdx() const {
        return m_headIdx;
    }

private:
    std::size_t m_headIdx{};
    std::size_t m_tailIdx{};
    std::array<T, N> m_data;
};

} // namespace lockfree
#endif //LOCK_FREE_DATA_STRUCTURE_SPSC_BOUNDED_QUEUE_HPP 
