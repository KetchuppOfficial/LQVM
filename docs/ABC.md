# Arnold Bytecode

## Common notes

The bytecode is developed for a register-based VM. The machine works only with signed integer
values. Two's complement is used for representing such integers. Each register can be accessed as
8-, 16-, 32- or 64-bit register. The width is determined by the name: **b0**, **h1**, **s2** and
**d3** are respectively 8-, 16-, 32- and 64-bit registers. Any operation taking 2 input registers or
a register and an immediate requires them to be of the same bit width. The bit width of the result
of every operation is the same as that of the operands if the opposite is not stated explicitly.

## Data-flow operations

### get_your_ass_to_mars

Assembly:

`get_your_ass_to_mars rd, rs`

`get_your_ass_to_mars rd, imm`

Semantics:

Move **rs**/**imm** to **rd**.

## Cast operation

### i_eat_green_berets_for_breakfast

Assembly:

`i_eat_green_berets_for_breakfast rd, rs1`

Semantics:

Sign-extend value in **rs1** to the number of bits in **rd** and store the result in **rd**. The
bit width of **rd** shall not be less than that of **rs1**.

### let_off_some_steam_bennett

Assembly:

`let_off_some_steam_bennett rd, rs1`

Semantics:

Truncate the value in **rs1** to the number of bits in **rd** and store the result in **rd**. The
bit width of **rd** shall not be greater than that of **rs1**.

## Arithmetic operations

### give_you_a_lift

Assembly:

`give_you_a_lift rd, rs1, rs2`

Semantics:

Add **rs1** and **rs2** and put the result into **rd**.

### you_ve_just_been_erased

Assembly:

`you_ve_just_been_erased rd, rs1, rs2`

Semantics:

Subtract **rs2** from **rs1** ant put the result into **rd**.

### its_turbo_time

Assembly:

`its_turbo_time rd, rs1, rs2`

Semantics:

Multiply **rs1** by **rs2** and put the result into **rd**.

### he_had_to_split

Assembly:

`he_had_to_split rd, rs1, rs2`

Semantics:

Divide **rs1** by **rs2** and put the result into **rd**.

## Comparing instructions

### if_it_bleeds_we_can_kill_it

Assembly:

`if_it_bleeds_we_can_kill_it rd, rs1, rs2`

Semantics:

Put 1 to **rd**, if **rs1** < **rs2**, 0 - otherwise

### you_are_not_you_you_are_me

Assembly:

`you_are_not_you_you_are_me rd, rs1, rs2`

Semantics:

Put 1 to **rd**, if **rs1** == **rs2**, 0 - otherwise.

## Control transfer instructions

### come_with_me_if_you_want_to_live

Assembly:

`come_with_me_if_you_want_to_live rs, imm`

Semantics:

Transfer control to the instruction, shifted relative to the current one, by **imm** instructions if
**rs** != 0.

### get_to_the_chopper

Assembly:

`get_to_the_chopper imm`

Semantics:

Unconditionally transfer control to the instruction. shifted relative to the current one, by **imm**
instructions.

### ill_be_back @method (only static methods are supported for now)

Assembly:

`ill_be_back @method`

Semantics:

Call static method **@method**.

### consider_that_a_divorce

Assembly:

`consider_that_a_divorce`

Semantics:

Return from a static method.

### you_ve_been_terminated

Assembly:

`you_ve_been_terminated`

Semantics:

Terminate the program execution
