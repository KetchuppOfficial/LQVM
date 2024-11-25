#ifndef INCLUDE_BYTECODE_FUNCTION_HPP
#define INCLUDE_BYTECODE_FUNCTION_HPP

#include <cstdint>
#include <utility>
#include <string>
#include <string_view>
#include <vector>

#include "utils/common.hpp"

namespace lqvm
{


/* Class representing a function
 *
 * On creation specify function's name, the number of arguments, the number of local variables,
 * and the number of return values.
 *
 * Then, add all constants used in the function and pointers to all other functions called from this
 * one.
 *
 * Lastly, fill the function with the bytecode.
 */
class Function final
{
public:

    Function(std::string name, unsigned short locals, unsigned char args, bool returns)
        : name_{std::move(name)}, locals_{locals}, args_{args}, has_return_value_{returns} {}

    Function(const Function &) = default;
    Function &operator=(const Function &) = default;

    Function(Function &&rhs) noexcept
        : name_{std::move(rhs.name_)},
          locals_{std::exchange(rhs.locals_, 0)},
          args_{std::exchange(rhs.args_, 0)},
          has_return_value_{std::exchange(rhs.has_return_value_, 0)},
          code_{std::move(rhs.code_)},
          constants_{std::move(rhs.constants_)},
          callees_{std::move(rhs.callees_)} {}

    Function &operator=(Function &&rhs) noexcept
    {
        swap(rhs);
        return *this;
    }

    void swap(Function &rhs) noexcept
    {
        name_.swap(rhs.name_);

        std::swap(locals_, rhs.locals_);
        std::swap(args_, rhs.args_);
        std::swap(has_return_value_, rhs.has_return_value_);

        code_.swap(rhs.code_);
        constants_.swap(rhs.constants_);
        callees_.swap(rhs.callees_);
    }

    // getters

    auto get_name() noexcept { return std::string_view{name_.data(), name_.size()}; }

    unsigned short n_locals() const noexcept { return locals_; }
    unsigned char n_args() const noexcept { return args_; }
    bool has_return_value() const noexcept { return has_return_value_; }

    auto &get_code() const noexcept { return code_; }
    auto &get_constants() const noexcept { return constants_; }
    auto &get_callees() const noexcept { return callees_; }

    // modifiers

    void add_const(uint64_t value) { constants_.push_back(value); }
    void add_callee(const Function *callee) { callees_.push_back(callee); }

    void add_GetYourAssToMars(uint8_t A, uint16_t B);
    void add_YouVeBeenTerminated();

    #undef DECLARE_ADD_ABC
    #define DECLARE_ADD_ABC(OP) void add_##OP(uint8_t A, uint16_t B, uint16_t C);

    DECLARE_ADD_ABC(GiveYouALift)
    DECLARE_ADD_ABC(YouVeJustBeenErased)
    DECLARE_ADD_ABC(ItSTurboTime)
    DECLARE_ADD_ABC(HeHadToSplit)
    DECLARE_ADD_ABC(LetOffSomeSteamBennet)
    DECLARE_ADD_ABC(IfItBleedsWeCanKillIt)
    DECLARE_ADD_ABC(YouAreAChoirBoyComparedToMe)
    DECLARE_ADD_ABC(YouAreNotYouYouAreMe)
    DECLARE_ADD_ABC(IllBeBack)

    #undef DECLARE_ADD_ABC

    #undef DECLARE_ADD_A_UIMM
    #define DECLARE_ADD_A_UIMM(OP) void add_##OP(uint8_t A, uint32_t simm);

    DECLARE_ADD_A_UIMM(PutThatCookieDownNow)
    DECLARE_ADD_A_UIMM(ConsiderThatADivorce)
    DECLARE_ADD_A_UIMM(TalkToTheHand)

    #undef DECLARE_ADD_A_UIMM

    #undef DECLARE_ADD_A_SIMM
    #define DECLARE_ADD_A_SIMM(OP) void add_##OP(uint8_t, int32_t simm);

    DECLARE_ADD_A_SIMM(ComeWithMeIfYouWantToLive)
    DECLARE_ADD_A_SIMM(GetToTheChopper)

    #undef DECLARE_ADD_A_SIMM

private:

    void check_BC(uint16_t BC);

    std::string name_;

    unsigned short locals_;
    unsigned char args_;
    bool has_return_value_;

    std::vector<BCInstr> code_;
    std::vector<Number> constants_;
    std::vector<const Function *> callees_;
};

} // namespace lqvm

#endif // INCLUDE_FUNCTION_HPP
