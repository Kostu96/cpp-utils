#pragma once

namespace cut {

template <typename T>
class PassKey
{
    friend T;
    explicit PassKey() = default;
};

} // namespace cut
