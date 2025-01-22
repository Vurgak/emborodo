#pragma once

#include <vector>

namespace en
{

class monotonic_allocator
{
public:
    /// 
    /// @param memory_size Size of the preallocated memory pool in bytes.
    explicit monotonic_allocator(std::size_t memory_size);

    template<typename T, typename... TArgs>
    T* allocate(TArgs&&... args);

    void release();

private:
    std::vector<std::byte> m_memory_pool;
    std::size_t m_offset = 0;
};

template<typename T, typename... TArgs>
T* monotonic_allocator::allocate(TArgs&&... args)
{
    const auto alignment = alignof(T);
    const auto address = (m_offset + alignment - 1) / alignment * alignment;
    const auto new_offset = address + sizeof(T);
    if (new_offset >= m_memory_pool.size())
        throw std::bad_alloc{};

    m_offset = new_offset;

    auto pointer = reinterpret_cast<void*>(m_memory_pool.data() + address);
    return new (pointer) T(std::forward<TArgs>(args)...);
}

}
