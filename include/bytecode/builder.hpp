#ifndef INCLUDE_BYTECODE_BUILDER_HPP
#define INCLUDE_BYTECODE_BUILDER_HPP

#include <cstdint>

#include "utils/common.hpp"
#include "utils/bits_manipulation.hpp"
#include "bytecode/opcodes.hpp"

namespace lqvm
{

class BytecodeBuilder final
{
public:
    explicit BytecodeBuilder() = default;

    static constexpr BCInstr create_GetYourAssToMars(uint8_t A, uint16_t B) noexcept
    {
        return create_AB<Opcodes::kGetYourAssToMars>(A, B);
    }

    static constexpr BCInstr create_ComeWithMeIfYouWantToLive(uint8_t A, int32_t simm) noexcept
    {
        return create_SIMM<Opcodes::kComeWithMeIfYouWantToLive>(A, simm);
    }

    static constexpr BCInstr create_GetToTheChopper(int32_t simm) noexcept
    {
        return create_SIMM<Opcodes::kGetToTheChopper>(0, simm);
    }

    static constexpr BCInstr create_YouVeBeenTerminated() noexcept
    {
        return Opcodes::kYouVeBeenTerminated;
    }

    #undef DEFINE_A_UIMM
    #define DEFINE_A_UIMM(OP)                                               \
    static constexpr BCInstr create_##OP(uint8_t A, uint32_t uimm) noexcept \
    {                                                                       \
        return create_UIMM<Opcodes::k##OP>(A, uimm);                        \
    }

    DEFINE_A_UIMM(PutThatCookieDownNow)
    DEFINE_A_UIMM(TalkToTheHand)
    DEFINE_A_UIMM(ConsiderThatADivorce)

    #undef DEFINE_A_UIMM

    #undef DEFINE_ABC
    #define DEFINE_ABC(OP)                                                           \
    static constexpr BCInstr create_##OP(uint8_t A, uint16_t B, uint16_t C) noexcept \
    {                                                                                \
        return create_ABC<Opcodes::k##OP>(A, B, C);                                  \
    }

    DEFINE_ABC(GiveYouALift)
    DEFINE_ABC(YouVeJustBeenErased)
    DEFINE_ABC(ItSTurboTime)
    DEFINE_ABC(HeHadToSplit)
    DEFINE_ABC(LetOffSomeSteamBennet)
    DEFINE_ABC(IfItBleedsWeCanKillIt)
    DEFINE_ABC(YouAreAChoirBoyComparedToMe)
    DEFINE_ABC(YouAreNotYouYouAreMe)
    DEFINE_ABC(IllBeBack)

    #undef DEFINE_ABC

private:

    template<Opcodes opcode>
    static constexpr BCInstr create_AB(uint8_t A, uint16_t B) noexcept
    {
        return (opcode)
             | (BCInstr{A} << kAFirstBit)
             | (BCInstr{mask_bits<kBCBitsLen - 1, 0>(B)} << kBFirstBit);
    }

    template<Opcodes opcode>
    static constexpr BCInstr create_ABC(uint8_t A, uint16_t B, uint16_t C) noexcept
    {
        return (create_AB<opcode>(A, B))
             | (BCInstr{mask_bits<kBCBitsLen - 1, 0>(C)} << kCFirstBit);
    }

    template<Opcodes opcode>
    static constexpr BCInstr create_UIMM(uint8_t A, uint32_t uimm) noexcept
    {
        return (opcode)
             | (BCInstr{A} << kAFirstBit)
             | (BCInstr{mask_bits<kIMMBitsLen - 1, 0>(uimm)} << kIMMFirstBit);
    }

    template<Opcodes opcode>
    static constexpr BCInstr create_SIMM(uint8_t A, int32_t simm) noexcept
    {
        return create_UIMM<opcode>(A, static_cast<uint32_t>(simm));
    }
};

} // lqvm

#endif // INCLUDE_BC_BUILDER_HPP
