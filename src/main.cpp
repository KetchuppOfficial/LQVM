#include <string>
#include <exception>

#include <CLI/CLI.hpp>
#include <fmt/base.h>

#include "bytecode/bytecode.hpp"
#include "lqvm.hpp"

namespace
{

lqvm::Bytecode factorial(unsigned n)
{
    /* constants = {0, n}
     *
     * you_are_not_you_you_are_me 1, 0, 0x0100
     * come_with_me_if_you_want_to_live 1, 5
     *
     * you_ve_just_been_erased 2, 0, 0x0101
     * i_ll_be_back 0, 2, 1
     * it_s_turbo_time 0, 0, 1
     * consider_that_a_divorce 0, 1
     *
     * put_that_cookie_down_now 1, 1
     * consider_that_a_divorce 1, 1
     */

    lqvm::Bytecode bc;

    auto &main = bc.create_function("main", 2, 0, 0);
    auto &fact = bc.create_function("factorial", 2, 1, 1);

    main.add_const(n);

    main.add_callee(&fact);

    main.add_PutThatCookieDownNow(1, 0);
    main.add_IllBeBack(0, 1, 1);
    main.add_TalkToTheHand(0, 1);
    main.add_YouVeBeenTerminated();

    fact.add_const(0);
    fact.add_const(1);

    fact.add_callee(&fact);

    fact.add_YouAreNotYouYouAreMe(1, 0x0000, 0x0100);
    fact.add_ComeWithMeIfYouWantToLive(1, 5);

    fact.add_YouVeJustBeenErased(2, 0, 0x0101);
    fact.add_IllBeBack(0, 2, 1);
    fact.add_ItSTurboTime(0, 0, 1);
    fact.add_ConsiderThatADivorce(0, 1);

    fact.add_PutThatCookieDownNow(1, 1);
    fact.add_ConsiderThatADivorce(1, 1);

    return bc;
}

} // unnamed_namespace

int main(int argc, char **argv) try
{
    CLI::App app{"LQVM: Low Quality Virtual Machine"};

    unsigned n;
    app.add_option("number", n, "the number which factorial to compute")
        ->required();

    CLI11_PARSE(app, argc, argv);

    auto bc = factorial(n);
    lqvm::LQVM vm{bc};
    vm.run();

    return 0;
}
catch (const std::exception &e)
{
    fmt::println(stderr, "Caught as instance of {}.\nwhat(): {}", typeid(e).name(), e.what());
    return 1;
}
catch (...)
{
    fmt::println(stderr, "Caught an unknown exception");
    return 1;
}
