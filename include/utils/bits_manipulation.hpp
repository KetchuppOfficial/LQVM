#ifndef INCLUDE_BITS_MANIPULATION
#define INCLUDE_BITS_MANIPULATION

#include <bit>
#include <climits>
#include <cstddef>
#include <concepts>
#include <type_traits>

namespace lqvm
{

static_assert(std::endian::native == std::endian::little);

template<std::integral T>
constexpr std::size_t kNBits = sizeof(T) * CHAR_BIT;

/*
 * Masks bits [to; from] (from <= to) of the input
 *
 *  15  13               5         0
 *   0 1 0 0 1 0 1 1 1 0 1 0 0 1 1 0 -----> 0000101110100000
 *       ^               ^
 *       to             from
 */
template<std::size_t to, std::size_t from, std::unsigned_integral T>
constexpr T mask_bits(T num) noexcept
{
    static_assert(from < to);
    static_assert(to < kNBits<T>);

    auto mask = []
    {
        if constexpr (to == kNBits<T> - 1)
            return ~T{0} - ((T{1} << from) - 1);
        else
            return (T{1} << (to + 1)) - (T{1} << from);
    }();

    return num & mask;
}

/*
 * Returns bits [to; from] (from <= to) of the input shifted to the low bits
 *
 *  15  13               5         0
 *   0 1 0 0 1 0 1 1 1 0 1 0 0 1 1 0 -----> 0000000001011101
 *       ^               ^
 *       to             from
 */
template<std::size_t to, std::size_t from, std::unsigned_integral T>
constexpr T get_bits(T num) noexcept
{
    static_assert(from < to);
    static_assert(to < kNBits<T>);

    return mask_bits<to, from>(num) >> from;
}

/*
 * The same as get_bits() but stores the result in a type possible different from the type of the
 * input, but long enough to store the bits in range [to; from]
 */
template<std::size_t to, std::size_t from, std::unsigned_integral R, std::unsigned_integral T>
constexpr R get_bits_r(T num) noexcept
{
    static_assert(from < to);
    static_assert(to < kNBits<T>);
    static_assert(to - from < kNBits<R>);

    return static_cast<R>(get_bits<to, from>(num));
}

/*
 * Masks a single bit of the input
 *
 *  15                             0
 *   0 1 0 0 1 0 1 1 1 0 1 0 0 1 1 0 -----> 0000000000100000
 *                       ^
 *                       n
 */
template<std::size_t n, std::unsigned_integral T>
constexpr T mask_bit(T num) noexcept
{
    static_assert(n < kNBits<T>);

    return num & (T{1} << n);
}

template<std::unsigned_integral T>
constexpr auto to_signed(T num) noexcept { return static_cast<std::make_signed_t<T>>(num); }

template<std::signed_integral T>
constexpr auto to_unsigned(T num) noexcept { return static_cast<std::make_unsigned_t<T>>(num); }

} // namespace lqvm

#endif // INCLUDE_BITS_MANIPULATION
