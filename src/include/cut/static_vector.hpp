#pragma once
#include "cut/exception.hpp"

#include <memory>

namespace cut {

// This is simplified std::inplace_vector
// TODO(Kostu): replace this with above when C++26 becomes adopted
template<typename T, std::size_t Capacity>
class StaticVector {
public:
    StaticVector() noexcept = default;

    ~StaticVector() { clear(); }

    // TODO(Kostu): Disable copy/move for now
    StaticVector(const StaticVector&) = delete;
    StaticVector& operator=(const StaticVector&) = delete;

    std::size_t size() const noexcept { return size_; }
    static constexpr std::size_t capacity() noexcept { return Capacity; }
    bool empty() const noexcept { return size_ == 0; }

    T& operator[](std::size_t i) {
        cut::ensure(i < size_, "Index out of bounds: {}", i);
        return *std::launder(reinterpret_cast<T*>(&storage_[i]));
    }

    const T& operator[](std::size_t i) const {
        cut::ensure(i < size_, "Index out of bounds: {}", i);
        return *std::launder(reinterpret_cast<const T*>(&storage_[i]));
    }

    template<typename ...Args>
    T& emplace_back(Args&& ...args) {
        cut::ensure(size_ < Capacity, "Storage overflow");
        T* ptr = std::construct_at(
            reinterpret_cast<T*>(&storage_[size_]),
            std::forward<Args>(args)...);
        ++size_;
        return *std::launder(ptr);
    }

    void pop_back() {
        cut::ensure(size_ > 0, "Storage is empty!");
        std::destroy_at(&(*this)[size_ - 1]);
        --size_;
    }

    void clear() {
        while (size_ > 0) { pop_back(); }
    }

    T* begin() { return data(); }
    T* end() { return data() + size_; }
    const T* begin() const { return data(); }
    const T* end() const { return data() + size_; }
private:
    T* data() { return std::launder(reinterpret_cast<T*>(storage_)); }
    const T* data() const { return std::launder(reinterpret_cast<const T*>(storage_)); }

    alignas(T) std::byte storage_[Capacity * sizeof(T)]{};
    std::size_t size_ = 0;
};

} // namespace cut
