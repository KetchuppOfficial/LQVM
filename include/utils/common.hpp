#ifndef INCLUDE_COMMON_HPP
#define INCLUDE_COMMON_HPP

#include <cstdint>

namespace lqvm
{

using BCInstr = uint32_t;
using Number = uint64_t;

constexpr BCInstr kOpcodeNBits = 6;

constexpr BCInstr kABitsLen = 8;
constexpr BCInstr kAFirstBit = kOpcodeNBits;
constexpr BCInstr kALastBit = kAFirstBit + kABitsLen - 1;

constexpr BCInstr kBCBitsLen = 9;

constexpr BCInstr kBFirstBit = kALastBit + 1;
constexpr BCInstr kBLastBit = kBFirstBit + kBCBitsLen - 1;

constexpr BCInstr kCFirstBit = kBLastBit + 1;
constexpr BCInstr kCLastBit = kCFirstBit + kBCBitsLen - 1;

constexpr BCInstr kIMMBitsLen = 2 * kBCBitsLen;
constexpr BCInstr kIMMFirstBit = kBFirstBit;
constexpr BCInstr kIMMLastBit = kCLastBit;

} // namespace lqvm

#endif // INCLUDE_COMMON_HPP
