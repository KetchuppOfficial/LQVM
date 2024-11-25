#include <cstddef>
#include <concepts>
#include <type_traits>
#include <functional>
#include <stdexcept>
#include <format>

#include "fmt/base.h"

#include "utils/common.hpp"
#include "utils/bits_manipulation.hpp"

#include "bytecode/opcodes.hpp"

#include "lqvm.hpp"

namespace lqvm
{

LQVM::LQVM(const Bytecode &bytecode) : bytecode_{bytecode}, value_stack_(kMaxStackSize)
{
    // do not reserve whole possible size but at least some
    call_stack_.reserve(bytecode_.n_functions());
    call_stack_.emplace_back(&bytecode_.get_entry(), 0);
}

namespace
{

auto get_A(BCInstr instr) noexcept { return get_bits_r<kALastBit, kAFirstBit, uint8_t>(instr); }
auto get_B(BCInstr instr) noexcept { return get_bits_r<kBLastBit, kBFirstBit, uint16_t>(instr); }
auto get_C(BCInstr instr) noexcept { return get_bits_r<kCLastBit, kCFirstBit, uint16_t>(instr); }
auto get_UIMM(BCInstr instr) noexcept { return get_bits<kIMMLastBit, kIMMFirstBit>(instr); }
auto get_SIMM(BCInstr instr) noexcept { return to_signed(get_UIMM(instr)); }

} // unnamed namespace

Number LQVM::get_reg_or_const(const Function *func, std::size_t base, uint32_t BC) const noexcept
{
    auto index = mask_bits<kBCBitsLen - 2, 0>(BC);
    if (mask_bit<kBCBitsLen - 1>(BC))
        return func->get_constants()[index];
    return value_stack_[base + index];
}

template<std::regular_invocable<Number, Number> F>
void LQVM::execute_binary_op(const Function *func, std::size_t base, BCInstr instr, F op)
noexcept(std::is_nothrow_invocable_v<F, Number, Number>)
{
    value_stack_[base + get_A(instr)] = op(get_reg_or_const(func, base, get_B(instr)),
                                           get_reg_or_const(func, base, get_C(instr)));
}

void LQVM::run()
{
entry:

    auto &frame = call_stack_.back();
    auto *func = frame.func;
    auto &code = func->get_code();
    auto base = frame.begin;

    while (frame.pc != code.size())
    {
        auto instr = code[frame.pc];

        switch (get_bits<kOpcodeNBits - 1, 0>(instr))
        {
            case Opcodes::kGetYourAssToMars:
                value_stack_[base + get_A(instr)] = value_stack_[base + get_B(instr)];
                ++frame.pc;
                break;

            case Opcodes::kPutThatCookieDownNow:
                value_stack_[base + get_A(instr)] = func->get_constants()[get_UIMM(instr)];
                ++frame.pc;
                break;

            case Opcodes::kGiveYouALift:
                execute_binary_op(func, base, instr, std::plus{});
                ++frame.pc;
                break;

            case Opcodes::kYouVeJustBeenErased:
                execute_binary_op(func, base, instr, std::minus{});
                ++frame.pc;
                break;

            case Opcodes::kItSTurboTime:
                execute_binary_op(func, base, instr, std::multiplies{});
                ++frame.pc;
                break;

            case Opcodes::kHeHadToSplit:
                execute_binary_op(func, base, instr, std::divides{});
                ++frame.pc;
                break;

            case Opcodes::kLetOffSomeSteamBennet:
                execute_binary_op(func, base, instr, std::modulus{});
                ++frame.pc;
                break;

            case Opcodes::kIfItBleedsWeCanKillIt:
                execute_binary_op(func, base, instr, std::less{});
                ++frame.pc;
                break;

            case Opcodes::kYouAreAChoirBoyComparedToMe:
                execute_binary_op(func, base, instr, std::less_equal{});
                ++frame.pc;
                break;

            case Opcodes::kYouAreNotYouYouAreMe:
                execute_binary_op(func, base, instr, std::equal_to{});
                ++frame.pc;
                break;

            case Opcodes::kComeWithMeIfYouWantToLive:
                frame.pc += (value_stack_[base + get_A(instr)] == 0) ? 1 : get_SIMM(instr);
                break;

            case Opcodes::kGetToTheChopper:
                frame.pc += get_SIMM(instr);
                break;

            case Opcodes::kIllBeBack:
            {
                ++frame.pc;

                std::size_t new_base;
                if (auto offset = get_B(instr)) // function with arguments
                    new_base = base + offset;
                else
                    new_base = base + func->n_args() + func->n_locals();

                call_stack_.emplace_back(func->get_callees()[get_A(instr)], new_base);

                // God, forgive me for this
                goto entry;
            }

            case Opcodes::kConsiderThatADivorce:
            {
                if (get_B(instr))
                    value_stack_[base - 1] = value_stack_[base + get_A(instr)];

                call_stack_.pop_back();

                // God, forgive me for this
                goto entry;
            }

            case Opcodes::kYouVeBeenTerminated:
                return;

            case Opcodes::kTalkToTheHand:
            {
                auto A = get_A(instr);
                auto n = get_UIMM(instr);
                for (decltype(n) i = 0; i != n; ++i)
                {
                    auto index = base + A + i;
                    fmt::println("R[{}] = {}", index, value_stack_[index]);
                }
                ++frame.pc;
                break;
            }

            default: [[unlikely]]
                throw std::runtime_error{std::format("unknown instruction {:#x}", instr)};
        }
    }
}

} // namespace lqvm
