#ifndef INCLUDE_OPCODES_HPP
#define INCLUDE_OPCODES_HPP

#include "common.hpp"

namespace lqvm
{

enum Opcodes : BCInstr
{
    // get_your_ass_to_mars
    kGYATM = 1,

    // put_that_cookie_down_now
    kPTCDN,

    // give_you_a_lift
    kGYAL,

    // you_ve_just_been_erased
    kYVJBE,

    // it_s_turbo_time
    kISTT,

    // he_had_to_split
    kHHTS,

    // let_off_some_steam_bennet
    kLOSSB,

    // if_it_bleeds_we_can_kill_it
    kIIBWCKI,

    // you_are_a_choir_boy_compared_to_me
    kYAACBCTM,

    // you_are_not_you_you_are_me
    kYANYYAM,

    // come_with_me_if_you_want_to_live
    kCWMIYWTL,

    // get_to_the_chopper
    kGTTC,

    // i_ll_be_back
    kILBB,

    // consider_that_a_divorce
    kCTAD,

    // you_ve_been_terminated
    kYVBT = (BCInstr{1} << kOpcodeNBits) - 1,
};

} // namespace lqvm

#endif // INCLUDE_OPCODES_HPP
