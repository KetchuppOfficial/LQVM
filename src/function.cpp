#include <cstdint>
#include <format>
#include <stdexcept>

#include "utils/common.hpp"
#include "utils/bits_manipulation.hpp"

#include "bytecode/builder.hpp"
#include "bytecode/function.hpp"

namespace lqvm
{

void Function::add_GetYourAssToMars(uint8_t A, uint16_t B)
{
    if (mask_bit<kBCBitsLen - 1>(B) != 0)
        throw std::invalid_argument{
            "AB-format instructions doesn't use B to address constants"};
    code_.push_back(BytecodeBuilder::create_GetYourAssToMars(A, get_bits<kBCBitsLen - 1, 0>(B)));
}

void Function::add_ComeWithMeIfYouWantToLive(uint8_t A, int32_t simm)
{
    code_.push_back(BytecodeBuilder::create_ComeWithMeIfYouWantToLive(A, simm));
}

void Function::add_GetToTheChopper(int32_t simm)
{
    code_.push_back(BytecodeBuilder::create_GetToTheChopper(simm));
}

void Function::add_YouVeBeenTerminated()
{
    code_.push_back(BytecodeBuilder::create_YouVeBeenTerminated());
}


#undef DEFINE_ADD_ABC
#define DEFINE_ADD_ABC(OP)                                  \
void Function::add_##OP(uint8_t A, uint16_t B, uint16_t C)  \
{                                                           \
    check_BC(B);                                            \
    check_BC(C);                                            \
    B = get_bits<kBCBitsLen - 1, 0>(B);                     \
    C = get_bits<kBCBitsLen - 1, 0>(C);                     \
    code_.push_back(BytecodeBuilder::create_##OP(A, B, C)); \
}

DEFINE_ADD_ABC(GiveYouALift)
DEFINE_ADD_ABC(YouVeJustBeenErased)
DEFINE_ADD_ABC(ItSTurboTime)
DEFINE_ADD_ABC(HeHadToSplit)
DEFINE_ADD_ABC(LetOffSomeSteamBennet)
DEFINE_ADD_ABC(IfItBleedsWeCanKillIt)
DEFINE_ADD_ABC(YouAreAChoirBoyComparedToMe)
DEFINE_ADD_ABC(YouAreNotYouYouAreMe)
DEFINE_ADD_ABC(IllBeBack)

#undef DEFINE_ADD_ABC

#undef DEFINE_ADD_A_UIMM
#define DEFINE_ADD_A_UIMM(OP)                               \
void Function::add_##OP(uint8_t A, uint32_t uimm)           \
{                                                           \
    code_.push_back(BytecodeBuilder::create_##OP(A, uimm)); \
}

DEFINE_ADD_A_UIMM(PutThatCookieDownNow)
DEFINE_ADD_A_UIMM(ConsiderThatADivorce)
DEFINE_ADD_A_UIMM(TalkToTheHand)

#undef DEFINE_ADD_A_UIMM

void Function::check_BC(uint16_t BC)
{
    if (mask_bit<kBCBitsLen - 1>(BC) && mask_bits<kBCBitsLen - 2, 0>(BC) >= constants_.size())
    {
        throw std::out_of_range{
            std::format("requested addressing constant {}, but function has only {} constants",
                        BC, constants_.size())};
    }
}

} // namespace lqvm
