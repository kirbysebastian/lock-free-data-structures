#ifndef LOCK_FREE_DATA_STRUCTURE_SPSC_BOUNDED_QUEUE_HPP
#define LOCK_FREE_DATA_STRUCTURE_SPSC_BOUNDED_QUEUE_HPP

#include <atomic>
#include <memory>

#include "utils.hpp"

/*
 * (& (N - 1)) is a mask similar with modulo but more efficient.
 */

#define CACHE_LINE_SIZE 64

namespace lockfree {

template <typename T, std::size_t N>
requires utils::IsPowerOfTwo<N>
class SPSCBoundedQueue final {
public:

    bool tryPush(T&& value) noexcept {
		const auto currentHead{m_headIdx.load(std::memory_order::relaxed)};
        if (N == (currentHead - m_tailIdx.load(std::memory_order::relaxed))) {
            return false;
        }

        //m_data[currentHead & (N - 1)] = std::forward<T>(value); // NOTE: might throw, but should be fine, right??
		std::construct_at(std::addressof(m_data[currentHead & (N - 1)]), value);
		m_headIdx.store(currentHead + 1, std::memory_order::release);
        return true;
    }

    bool tryPop(T& value) noexcept {
		const auto currTail{m_tailIdx.load(std::memory_order::relaxed)};
        if (currTail == m_headIdx.load(std::memory_order::acquire)) {
            return false;
        }

        value = m_data[currTail & (N - 1)];
		std::destroy_at(std::addressof(m_data[currTail & (N - 1)]));
		m_tailIdx.store(currTail + 1, std::memory_order::relaxed);
        return true;
    }

	/*
    template <class... Args>
    bool emplace(Args&&... args) noexcept {
        return false; // @TODO: Implement me!
    }
	*/

    bool isFull() const noexcept {
		return N == (
		    m_headIdx.load(std::memory_order::relaxed) -
				m_tailIdx.load(std::memory_order::relaxed));
    }

    bool isEmpty() const noexcept {
        return m_headIdx.load(std::memory_order::relaxed) ==
			m_tailIdx.load(std::memory_order::relaxed);
    }

    constexpr std::size_t capacity() const noexcept {
        return N;
    }

    std::size_t size() const noexcept {
        return m_headIdx.load(std::memory_order::relaxed) -
			m_tailIdx.load(std::memory_order::relaxed);
    }

private:
    alignas(CACHE_LINE_SIZE) std::atomic<std::size_t> m_headIdx{};
    alignas(CACHE_LINE_SIZE) std::atomic<std::size_t> m_tailIdx{};
	T m_data[N];
};

} // namespace lockfree
#endif //LOCK_FREE_DATA_STRUCTURE_SPSC_BOUNDED_QUEUE_HPP 
