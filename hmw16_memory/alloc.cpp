#pragma once

#include <cstddef>
#include <new>
#include <limits>

template <typename T>
class allocator
{
public:
    using value_type=T;
allocator() noexcept=default;

    template<typename U>
    allocator(const allocator<U>&) noexcept
    {
    }
    T* allocate(std::size_t n)
    {
        if(n > std::numeric_limits<std::size_t>::max()/sizeof(T))
        {
            throw std::bad_array_new_length();
        }
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p,std::size_t) noexcept
    {
        ::operator delete(p);
    }
    template<typename U>
    bool operator==(const allocator<U>&) const noexcept
    {
        return true;
    }
    template<typename U>
    bool operator!=(const allocator<U>&) const noexcept
    {
        return false;
    }
};
