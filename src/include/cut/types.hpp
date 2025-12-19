#pragma once
#include <cstdint>

namespace cut {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using f32 = float;
static_assert(sizeof(f32) == 4);
using f64 = double;
static_assert(sizeof(f64) == 8);

inline u8 to_u8(auto v) { return static_cast<u8>(v); }
inline u16 to_u16(auto v) { return static_cast<u16>(v); }
inline u32 to_u32(auto v) { return static_cast<u32>(v); }
inline u64 to_u64(auto v) { return static_cast<u64>(v); }

inline s8 to_s8(auto v) { return static_cast<s8>(v); }
inline s16 to_s16(auto v) { return static_cast<s16>(v); }
inline s32 to_s32(auto v) { return static_cast<s32>(v); }
inline s64 to_s64(auto v) { return static_cast<s64>(v); }

inline f32 to_f32(auto v) { return static_cast<f32>(v); }
inline f64 to_f64(auto v) { return static_cast<f64>(v); }

} // namespace cut
