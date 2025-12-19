#pragma once
#include <cstddef>
#include <unordered_map>
#include <string>

namespace cut {

struct TransparentHash {
    using is_transparent = void;

    template<typename T>
    std::size_t operator()(const T& v) const noexcept {
        return std::hash<std::string_view>{}(v);
    }
};

struct TransparentEqual {
    using is_transparent = void;

    template<typename A, typename B>
    bool operator()(const A& lhs, const B& rhs) const noexcept {
        return std::string_view(lhs) == std::string_view(rhs);
    }
};

template<typename T>
using StringMap = std::unordered_map<std::string, T, TransparentHash, TransparentEqual>;

} // namespace cut
