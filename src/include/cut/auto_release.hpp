#pragma once
#include <cut/non_copyable.hpp>

#include <utility>

namespace cut {

template<typename T, typename Deleter = void(*)(T), T Invalid = T{}>
requires std::is_trivially_copyable_v<T>
class AutoRelease :
    NonCopyable {
public:
    AutoRelease() noexcept :
        handle_(Invalid),
        deleter_() {}
    
    explicit AutoRelease(T v, Deleter d = {}) noexcept :
        handle_(v),
        deleter_(std::move(d)) {}

    AutoRelease(AutoRelease&& other) noexcept :
        handle_(std::exchange(other.handle_, Invalid)),
        deleter_(std::move(other.deleter_)) {}
        
    ~AutoRelease() { reset(); }
    
    T get() const noexcept { return handle_; }
    
    void reset(T v = Invalid) noexcept {
        if (deleter_) {
            deleter_(handle_);
        }
        handle_ = v;
    }
    
    void swap(AutoRelease &other) noexcept
    {
        using std::swap;
        swap(handle_, other.handle_);
        swap(deleter_, other.deleter_);
    }
    
    AutoRelease& operator=(AutoRelease&& other) noexcept {
        if (this != &other) {
            reset();
            handle_ = std::exchange(other.handle_, Invalid);
            deleter_ = std::move(other.deleter_);
        }
        return *this;
    }
    
    T release() noexcept { return std::exchange(handle_, Invalid); }

    explicit operator bool() const noexcept { return handle_ != Invalid; }
private:
    T handle_;
    Deleter deleter_;
};

template<typename T, typename Deleter>
AutoRelease(T, Deleter) -> AutoRelease<T, Deleter>;

} // namespace cut
