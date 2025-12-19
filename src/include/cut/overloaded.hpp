#pragma once

namespace cut {

template<typename ...Args>
struct Overloaded : Args... {
    using Args::operator()...;
};

template<typename ...Args>
Overloaded(Args...) -> Overloaded<Args...>;

} // namespace cut
