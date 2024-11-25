# Arnold Bytecode

## Common notes

The bytecode is developed for a register-based Lua-like virtual machine.

All instructions occupy 32 bits and have an opcode in the low 6 bits.

Instructions have the following fields:

- **A**: 8 bits
- **B**: 9 bits
- **C**: 9 bits
- **UIMM**: 18 bits (unsigned immediate)
- **SIMM**: 18 bits (signed immediate)

The following notation is used in pseudocode to describe instructions' semantics:

- **R[X]** - register with index **X**

    **X** may be **A**, **B** or **C**. If **X** is either **B** or **C**, then only low 8 bits are
    considered.

- **K[X]** - constant with index **X**

    **X** may be only UIMM.

- **RK[X]** - register or constant

    **X** may be **B** or **C**.

    If the most significant bit of **X** is 0, **RK[X]** == **R[X]**.

    If the most significant bit of X is 1, **RK[X] == K[X[8:0]]**.

- **PC** (program counter) - special value representing the index of instruction being executed.

## Data-flow operations

### get_your_ass_to_mars

**Assembly:**

`get_your_ass_to_mars A, B`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `000000000` | `---------` | `--------` | `000001` |

**Semantics:**

```text
R[A] := R[B]
PC++
```

### put_that_cookie_down_now

**Assembly:**

`put_that_cookie_down_now A, imm`

**Encoding:**

|         UIMM         |     A      |  opcode  |
| -------------------- | ---------- | -------- |
| `------------------` | `--------` | `000010` |

**Semantics:**

```text
R[A] := K[UIMM]
PC++
```

## Arithmetic operations

### give_you_a_lift

**Assembly:**

`give_you_a_lift A, B, C`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `000011` |

**Semantics:**

```text
R[A] := RK[B] + RK[C]
PC++
```

### you_ve_just_been_erased

**Assembly:**

`you_ve_just_been_erased A, B, C`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `000100` |

**Semantics:**

```text
R[A] := RK[B] - RK[C]
PC++
```

### it_s_turbo_time

**Assembly:**

`it_s_turbo_time A, B, C`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `000101` |

**Semantics:**

```text
R[A] := RK[B] * RK[C]
PC++
```

### he_had_to_split

**Assembly:**

`he_had_to_split A, B, C`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `000110` |

**Semantics:**

```text
R[A] := RK[B] / RK[C]
PC++
```

### let_off_some_steam_bennet

**Assembly:**

`let_off_some_steam_bennet A, B, C`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `000111` |

**Semantics:**

```text
R[A] := RK[B] % RK[C]
PC++
```

## Comparison instructions

### if_it_bleeds_we_can_kill_it

**Assembly:**

`if_it_bleeds_we_can_kill_it A, B, C`

**Encoding:**

|      A      |      B      |     C      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `001000` |

**Semantics:**

```text
R[A] := RK[B] < RK[C] ? 1 : 0
PC++
```

### you_are_a_choir_boy_compared_to_me

**Assembly:**

`you_are_a_choir_boy_compared_to_me rd, rs1, rs2`

**Encoding:**

|      A      |      B      |     C      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `001001` |

**Semantics:**

```text
R[A] := RK[B] <= RK[C] ? 1 : 0
PC++
```

### you_are_not_you_you_are_me

**Assembly:**

`you_are_not_you_you_are_me A, B, C`

**Encoding:**

|      A      |      B      |     C      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `001010` |

**Semantics:**

```text
R[A] := RK[B] == RK[C] ? 1 : 0
PC++
```

## Control transfer instructions

### come_with_me_if_you_want_to_live

**Assembly:**

`come_with_me_if_you_want_to_live A, imm`

**Encoding:**

|         SIMM         |     A      |  opcode  |
| -------------------- | ---------- | -------- |
| `------------------` | `--------` | `001011` |

**Semantics:**

```text
PC += (R[A] == 0) ? 1 : SIMM
```

### get_to_the_chopper

**Assembly:**

`get_to_the_chopper imm`

**Encoding:**

|         SIMM         |     A      |  opcode  |
| -------------------- | ---------- | -------- |
| `------------------` | `00000000` | `001100` |

**Semantics:**

```text
PC += SIMM
```

### i_ll_be_back

**Assembly:**

`i_ll_be_back A, B, C`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `---------` | `---------` | `--------` | `001101` |

**Semantics:**

```text
if (B == 0)
    callee[A]()
else
    callee[A](R[B], ..., R[B + C - 1])
```

On function call a new stack frame is created. It's first registers are the arguments of the call.
If the function returns a value, a slot in the value stack shall be reserved for storing the value
at the top of the caller's frame just before the start of the callee's frame.

### consider_that_a_divorce

**Assembly:**

`consider_that_a_divorce A, UIMM`

**Encoding:**

|         UIMM         |     A      |  opcode  |
| -------------------- | ---------- | -------- |
| `------------------` | `--------` | `001110` |

**Semantics:**

If **R[UIMM] != 1**, return the value stored in **R[A]**. Otherwise, return from the function
without storing the return value.

### you_ve_been_terminated

**Assembly:**

`you_ve_been_terminated`

**Encoding:**

|      C      |      B      |     A      |  opcode  |
| ----------- | ----------- | ---------- | -------- |
| `000000000` | `000000000` | `00000000` | `001111` |

**Semantics:**

Terminate the program execution.

## Miscellaneous

### talk_to_the_hand

**Assembly:**

`talk_to_the_hand A, UIMM`

**Encoding:**

|         UIMM         |     A      |  opcode  |
| -------------------- | ---------- | -------- |
| `------------------` | `--------` | `010000` |

**Semantics:**

Print **R[A], ..., R[A + UIMM]** on standard output.
