#include <cassert>
#include <print>

#include "data-structures/SPSCBoundedQueue.hpp"

int main() {

    std::println("\nlock-free-ds");
    lockfree::SPSCBoundedQueue<std::uint64_t, 4> kyu;

    static_assert(4 == kyu.capacity());
    assert(0 == kyu.size());
    assert(true == kyu.isEmpty());
    assert(false == kyu.isFull());
    assert(true == kyu.tryPush(11));
    assert(1 == kyu.size());
    assert(true == kyu.tryPush(28));
    assert(2 == kyu.size());
    assert(true == kyu.tryPush(13));
    assert(3 == kyu.size());
    assert(true == kyu.tryPush(2));
    assert(4 == kyu.size());
    assert(true == kyu.isFull());
    assert(false == kyu.isEmpty());
    assert(false == kyu.tryPush(7));
    assert(4 == kyu.size());


    return EXIT_SUCCESS;
}
