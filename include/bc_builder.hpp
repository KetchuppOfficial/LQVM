#ifndef INCLUDE_BC_BUILDER_HPP
#define INCLUDE_BC_BUILDER_HPP

#include <cstdint>

#include "common.hpp"
#include "opcodes.hpp"
#include "bits_manipulation.hpp"

namespace lqvm
{

class BytecodeBuilder final
{
public:
    explicit BytecodeBuilder() = default;

    #define GENERATE_AB(OP)                                              \
    static constexpr BCInstr create_##OP(uint8_t A, uint16_t B) noexcept \
    {                                                                    \
        return create_AB<Opcodes::k##OP>(A, B);                          \
    }

    GENERATE_AB(GYATM)
    GENERATE_AB(CTAD)

    #undef GENERATE_AB

    #define GENERATE_ABC(OP)                                                         \
    static constexpr BCInstr create_##OP(uint8_t A, uint16_t B, uint16_t C) noexcept \
    {                                                                                \
        return create_ABC<Opcodes::k##OP>(A, B, C);                                  \
    }

    GENERATE_ABC(GYAL)
    GENERATE_ABC(YVJBE)
    GENERATE_ABC(ISTT)
    GENERATE_ABC(HHTS)
    GENERATE_ABC(LOSSB)
    GENERATE_ABC(IIBWCKI)
    GENERATE_ABC(YAACBCTM)
    GENERATE_ABC(YANYYAM)
    GENERATE_ABC(ILBB)

    #undef GENERATE_ABC

    #define GENERATE_SIMM(OP)                                              \
    static constexpr BCInstr create_##OP(uint8_t A, int32_t simm) noexcept \
    {                                                                      \
        return create_SIMM<Opcodes::k##OP>(A, simm);                       \
    }

    GENERATE_SIMM(CWMIYWTL)
    GENERATE_SIMM(GTTC)

    #undef GENERATE_UIMM

    // create put_that_cookie_down_now
    static constexpr BCInstr create_PTCDN(uint8_t A, uint32_t uimm) noexcept
    {
        return create_UIMM<Opcodes::kPTCDN>(A, uimm);
    }

    // create you_ve_been_terminated
    static constexpr BCInstr create_YVBT() noexcept { return Opcodes::kYVBT; }

private:

    template<Opcodes opcode>
    static constexpr BCInstr create_AB(uint8_t A, uint16_t B) noexcept
    {
        return (opcode)
             | (BCInstr{A} << kAFirstBit)
             | (BCInstr{mask_bits<kBBitsLen - 1, 0>(B)} << kBFirstBit);
    }

    template<Opcodes opcode>
    static constexpr BCInstr create_ABC(uint8_t A, uint16_t B, uint16_t C) noexcept
    {
        return (create_AB<opcode>(A, B))
             | (BCInstr{mask_bits<kCBitsLen - 1, 0>(C)} << kCFirstBit);
    }

    template<Opcodes opcode>
    static constexpr BCInstr create_UIMM(uint8_t A, uint32_t uimm) noexcept
    {
        return (opcode)
             | (BCInstr{A} << kAFirstBit)
             | (BCInstr{mask_bits<kIMMBitsLen - 1, 0>(uimm) << kIMMFirstBit});
    }

    template<Opcodes opcode>
    static constexpr BCInstr create_SIMM(uint8_t A, int32_t simm) noexcept
    {
        return create_UIMM<opcode>(A, static_cast<uint32_t>(simm));
    }
};

} // lqvm

#endif // INCLUDE_BC_BUILDER_HPP
