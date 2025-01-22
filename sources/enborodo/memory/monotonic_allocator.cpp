#include "monotonic_allocator.hpp"

namespace en
{

monotonic_allocator::monotonic_allocator(const std::size_t memory_size) :
    m_memory_pool{memory_size}
{
}

void monotonic_allocator::release()
{
    m_offset = 0;
}

}
