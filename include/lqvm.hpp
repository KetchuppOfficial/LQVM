#ifndef INCLUDE_LQVM_HPP
#define INCLUDE_LQVM_HPP

#include <cstddef>
#include <concepts>
#include <cstdlib>
#include <type_traits>
#include <vector>

#include <fmt/base.h>

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

    class ValueStack final
    {
    public:

        explicit ValueStack(std::size_t size) : value_stack_(size) {}

        template<typename Self>
        auto &&operator[](this Self &&self, std::size_t i) noexcept
        {
            if (i >= self.value_stack_.size()) [[unlikely]]
            {
                fmt::println(stderr, "stack overflow");
                std::exit(EXIT_FAILURE);
            }
            return self.value_stack_[i];
        }

    private:

        std::vector<Number> value_stack_;
    };

    Bytecode bytecode_;

    ValueStack value_stack_;
    std::vector<CallInfo> call_stack_;
};

} // namespace lqvm

#endif // INCLUDE_LQVM_HPP
