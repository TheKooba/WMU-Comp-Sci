# Assignment One: RPN Calculator

To practice writing assembly and passing parameters, you will implement the math functions of an **RPN calculator**. This stands for **R**everse **P**olish **N**otation and uses a stack to keep track of values.

The `add.S` and `sub.S` files will be trivial to complete, but `mul.S` and `divd.S` will take some careful planning. You must either repeatedly add or repeatedly subtract (and count) the first input number by the second.

When finished the calculator should be able to add, subtract, multiply and divide.

Here is an example session:

    $ 4 5 +

    0: 9
    1: -
    2: -
    3: -

    $ 16 -

    0: 7
    1: -
    2: -
    3: -

    $ 49 /

    0: 7
    1: -
    2: -
    3: -

    $ 2 3 4 *

    0: 7
    1: 2
    2: 12
    3: -

1. You should strive to complete this functionality in as _few instructions as possible_.
1. Only write your solution in the provided assembly files (inside the `func/` directory).
1. Use _repeated addition_ to calculate the result of multiplication. You will need to construct a loop yourself!
1. Use _repeated subtraction_ to calculate the quotient. Again, you will need to construct a loop yourself!
1. Do not simply generate assembly using the compiler and submit it. **I will know**.

### Parameter Passing

As we talked about in class, parameters are passed to functions in the registers `r15`, `r14`, `r13` and `r12` in that order. The top of the stack is the first argument in `r15` and the value underneath that is the second argument in `r14`. Remember, when the microcontroller executes the `ret` instruction at the end of a function, the return value should be in `r15`!

### Assembly Instructions

Here are some useful instructions you might need:

```
mov     src, dst    ; move the contents of src to dst
sub     src, dst    ; subtract the value in src from dst and store the result in dst
add     src, dst    ; add the value in src to the value in dst and store the result in dst
clr     dst         ; zero out destination (same as mov #0, dst)
jn      label       ; jump to label if N is set (result of previous instruction set N)
jmp     label       ; jump to label unconditionally (always)
```

A more complete listing can be found on page 56 of the [Family User's Guide](http://www.ti.com/lit/ug/slau144j/slau144j.pdf).

### Registers

You can use any of the registers `r4 - r15`, however do _not_ use registers `r0 - r3` for _anything_ in your function. These registers serve special purposes on the **MSP430**.

### Extra Credit

You may implement exponentiation and modulo in the `powr.S` and `mod.S` files if you would like to earn extra credit.
