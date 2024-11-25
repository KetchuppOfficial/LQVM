#ifndef INCLUDE_BYTECODE_BYTECODE_HPP
#define INCLUDE_BYTECODE_BYTECODE_HPP

#include <string>
#include <list>

#include "bytecode/function.hpp"

namespace lqvm
{

class Bytecode final : private std::list<Function>
{
    using Base = std::list<Function>;

public:

    explicit Bytecode() = default;

    const Function &get_entry() const noexcept { return front(); }

    // the first added function is considered the entry point of the program
    Function &create_function(const std::string &name, unsigned short locals,
                              unsigned char args, bool has_return_value)
    {
        return emplace_back(name, locals, args, has_return_value);
    }

    auto n_functions() const noexcept { return size(); }

    using Base::begin;
    using Base::end;
    using Base::cbegin;
    using Base::cend;
};

} // namespace lqvm

#endif // INCLUDE_BYTECODE_HPP
