#ifndef INCLUDE_LQVM_HPP
#define INCLUDE_LQVM_HPP

#include <cstddef>
#include <concepts>
#include <type_traits>
#include <vector>

#include "utils/common.hpp"

#include "bytecode/bytecode.hpp"

namespace lqvm
{

class LQVM final
{
public:

    static constexpr std::size_t kMaxStackSize = 4096;

    explicit LQVM(const Bytecode &bytecode);

    void run();

private:

    Number get_reg_or_const(const Function *func, std::size_t base, uint32_t BC) const noexcept;

    template<std::regular_invocable<Number, Number> F>
    void execute_binary_op(const Function *func, std::size_t base, BCInstr instr, F op)
    noexcept(std::is_nothrow_invocable_v<F, Number, Number>);

    struct CallInfo final
    {
        const Function *func;

        // index of the current function in value stack; arguments follow it immediately
        std::size_t begin;

        // pc of the current function
        std::size_t pc = 0;
    };

    Bytecode bytecode_;

    std::vector<Number> value_stack_;
    std::vector<CallInfo> call_stack_;
};

} // namespace lqvm

#endif // INCLUDE_LQVM_HPP
