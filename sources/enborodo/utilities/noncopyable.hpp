#pragma once

namespace en {

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;

protected:
    constexpr noncopyable() = default;
    ~noncopyable() = default;
};

} // en
