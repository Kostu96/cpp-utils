#pragma once

namespace cut {

class NonCopyable {
protected:
    constexpr NonCopyable() = default;

    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

} // namespace cut
