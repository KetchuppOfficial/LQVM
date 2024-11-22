#ifndef INCLUDE_COMMON_HPP
#define INCLUDE_COMMON_HPP

#include <cstdint>

namespace lqvm
{

using BCInstr = uint32_t;

constexpr BCInstr kOpcodeNBits = 6;

constexpr BCInstr kABitsLen = 8;
constexpr BCInstr kAFirstBit = kOpcodeNBits;
constexpr BCInstr kALastBit = kAFirstBit + kABitsLen - 1;

constexpr BCInstr kBBitsLen = 9;
constexpr BCInstr kBFirstBit = kALastBit + 1;
constexpr BCInstr kBLastBit = kBFirstBit + kBBitsLen - 1;

constexpr BCInstr kCBitsLen = 9;
constexpr BCInstr kCFirstBit = kBLastBit + 1;
constexpr BCInstr kCLastBit = kCFirstBit + kCBitsLen - 1;

constexpr BCInstr kIMMBitsLen = kBBitsLen + kCBitsLen;
constexpr BCInstr kIMMFirstBit = kBFirstBit;
constexpr BCInstr kIMMLastBit = kCLastBit;

} // namespace lqvm

#endif // INCLUDE_COMMON_HPP
