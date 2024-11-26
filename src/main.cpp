#include <string>
#include <utility>
#include <exception>

#include <CLI/CLI.hpp>
#include <fmt/base.h>
#include <utility>

#include "CLI/CLI.hpp"
#include "bytecode/bytecode.hpp"
#include "lqvm.hpp"

namespace
{

lqvm::Bytecode factorial(unsigned n)
{
    lqvm::Bytecode bc;

    auto &main = bc.create_function("main", 2, 0, 0);
    auto &fact = bc.create_function("factorial", 2, 1, 1);

    /* constants = {n}
     *
     * put_that_cookie_down_now 1, 0
     * i_ll_be_back 0, 1, 1
     * talk_to_the_hand 0, 1
     * you_ve_been_terminated
     */

    main.add_callee(&fact);
    main.add_const(n);

    main.add_PutThatCookieDownNow(1, 0);
    main.add_IllBeBack(0, 1, 1);
    main.add_TalkToTheHand(0, 1);
    main.add_YouVeBeenTerminated();

    /* constants = {0, 1}
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

    fact.add_callee(&fact);
    fact.add_const(0);
    fact.add_const(1);

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

lqvm::Bytecode fibonacci_recursion(unsigned n)
{
    lqvm::Bytecode bc;

    auto &main = bc.create_function("main", 2, 0, 0);
    auto &fibonacci = bc.create_function("fibonacci", 3, 1, 1);

    main.add_callee(&fibonacci);

    /* constants = {n}
     *
     * put_that_cookie_down_now 1, 0
     * i_ll_be_back 0, 1, 1
     * talk_to_the_hand 0, 1
     * you_ve_been_terminated
     */

    main.add_const(n);

    main.add_PutThatCookieDownNow(1, 0);
    main.add_IllBeBack(0, 1, 1);
    main.add_TalkToTheHand(0, 1);
    main.add_YouVeBeenTerminated();

    /* constant = {1, 2}
     *
     * you_are_not_you_you_are_me 1, 0, 0x0100
     * come_with_me_if_you_want_to_live 1, 9
     *
     * you_are_not_you_you_are_me 1, 0, 0x0101
     * come_with_me_if_you_want_to_live 1, 7
     *
     * you_ve_just_been_erased 2, 0, 0x0100
     * i_ll_be_back 0, 2, 1
     * you_ve_just_been_erased 3, 0, 0x0101
     * i_ll_be_back 0, 3, 1
     * give_you_a_lift 1, 1, 2
     * consider_that_a_divorce 1, 1
     *
     * put_that_cookie_down_now 1, 0
     * consider_that_a_divorce 1, 1
     */

    fibonacci.add_callee(&fibonacci);
    fibonacci.add_const(1);
    fibonacci.add_const(2);

    fibonacci.add_YouAreNotYouYouAreMe(1, 0, 0x0100);
    fibonacci.add_ComeWithMeIfYouWantToLive(1, 9);

    fibonacci.add_YouAreNotYouYouAreMe(1, 0, 0x0101);
    fibonacci.add_ComeWithMeIfYouWantToLive(1, 7);

    fibonacci.add_YouVeJustBeenErased(2, 0, 0x0100);
    fibonacci.add_IllBeBack(0, 2, 1);
    fibonacci.add_YouVeJustBeenErased(3, 0, 0x0101);
    fibonacci.add_IllBeBack(0, 3, 1);
    fibonacci.add_GiveYouALift(1, 1, 2);
    fibonacci.add_ConsiderThatADivorce(1, 1);

    fibonacci.add_PutThatCookieDownNow(1, 0);
    fibonacci.add_ConsiderThatADivorce(1, 1);

    return bc;
}

lqvm::Bytecode fibonacci_loop(unsigned n)
{
    lqvm::Bytecode bc;

    auto &main = bc.create_function("main", 2, 0, 0);
    auto &fibonacci = bc.create_function("fibonacci", 5, 1, 1);

    /* constants = {n}
     *
     * put_that_cookie_down_now 1, 0
     * i_ll_be_back 0, 1, 1
     * talk_to_the_hand 0, 1
     * you_ve_been_terminated
     */

    main.add_callee(&fibonacci);
    main.add_const(n);

    main.add_PutThatCookieDownNow(1, 0);
    main.add_IllBeBack(0, 1, 1);
    main.add_TalkToTheHand(0, 1);
    main.add_YouVeBeenTerminated();

    /* constant = {0, 1, 2}
     *
     * you_are_not_you_you_are_me 1, 0, 0x0101
     * come_with_me_if_you_want_to_live 1, 13
     *
     * you_ve_just_been_erased 0, 0, 0x0102
     * put_that_cookie_down_now 1, 0
     * put_that_cookie_down_now 3, 1
     * put_that_cookie_down_now 4, 1
     *
     * you_are_not_you_you_are_me 2, 0, 1
     * come_with_me_if_you_want_to_live 2, 6
     *
     * give_you_a_lift 5, 3, 4
     * get_your_ass_to_mars 3, 4
     * get_your_ass_to_mars 4, 5
     * give_you_a_lift 1, 1, 0x0101
     * get_to_the_chopper -6
     *
     * consider_that_a_divorce 4, 1
     *
     * put_that_cookie_down_now 1, 1
     * consider_that_a_divorce 1, 1
     */

    fibonacci.add_const(0);
    fibonacci.add_const(1);
    fibonacci.add_const(2);

    fibonacci.add_YouAreNotYouYouAreMe(1, 0, 0x0101);
    fibonacci.add_ComeWithMeIfYouWantToLive(1, 13);

    fibonacci.add_YouVeJustBeenErased(0, 0, 0x0102);
    fibonacci.add_PutThatCookieDownNow(1, 0);
    fibonacci.add_PutThatCookieDownNow(3, 1);
    fibonacci.add_PutThatCookieDownNow(4, 1);

    fibonacci.add_YouAreNotYouYouAreMe(2, 0, 1);
    fibonacci.add_ComeWithMeIfYouWantToLive(2, 6);

    fibonacci.add_GiveYouALift(5, 3, 4);
    fibonacci.add_GetYourAssToMars(3, 4);
    fibonacci.add_GetYourAssToMars(4, 5);
    fibonacci.add_GiveYouALift(1, 1, 0x0101);
    fibonacci.add_GetToTheChopper(-6);

    fibonacci.add_ConsiderThatADivorce(4, 1);

    fibonacci.add_PutThatCookieDownNow(1, 1);
    fibonacci.add_ConsiderThatADivorce(1, 1);

    return bc;
}

} // unnamed_namespace

int main(int argc, char **argv) try
{
    CLI::App app{"LQVM: Low Quality Virtual Machine"};

    unsigned n;
    app.add_option("number", n, "the input number")
        ->required();

    std::string program;
    app.add_option("--program", program, "the program to run")
        ->required()
        ->check(CLI::IsMember({"fibonacci-loop", "fibonacci-recursion", "factorial"}));

    CLI11_PARSE(app, argc, argv);

    auto bc = [&]
    {
        if (program == "fibonacci-loop")
            return fibonacci_loop(n);
        else if (program == "fibonacci-recursion")
            return fibonacci_recursion(n);
        else if (program == "factorial")
            return factorial(n);
        std::unreachable();
    }();

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
