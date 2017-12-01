# Assignment Zero: Base Conversion

You are to write a simple C program that will take a decimal number and a base as command line parameters and output the decimal number in that specified base. For example:

    $ ./conv 13 2
    1101
    $ ./conv 236709 8
    716245 
    $ ./conv 1352275 11
    843A91
    $ ./conv 38572856 64
    2J9Cu

    $ ./conv
    Usage: conv <decimal> <base>
    $ ./conv 11111 19
    INVALID BASE

1. Your program should be able to handle all bases from 2-16 and also base 64.
1. For bases that are powers of 2 (2, 4, 8, 16 and 64) you should use a **mask and shift** algorithm. See below.
1. Please name your code file `conv.c`. This will be the only file you submit to me (via the git server, we will get you connected to this on Wednesday, _so come prepared_).
1. Attempt to handle errors. You were shown a possible issue during class. Another problem could be an invalid base (see example output).
1. Use a buffer of **32 characters**. This will give you 31 locations for characters and the final location should be a null.
1. Remember: you have to put the digits into the buffer _backwards_ and when the algorithm is finished, you have to _printf from the correct location in that buffer_. See the example we did in class for how to accomplish that.

### Converting Integers to Characters

We saw one way to do this in class, but _this will not give you the correct character `A` for the value `10`_. Instead, think about how to use this character array:

```c
char *ascii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
```

You can declare this at the top of your file along with your buffer. How can you use this to accomplish a conversion to bases 11-16 and 64? Think about how to do this! It is just an array of characters ...

### Masking & Shifting

Along with the algorithm we saw in class of modulo followed by division, you can accomplish the same result on bases that are powers of two _by masking off the number of bits you need and then shifting the bits down_. Remember how the `&` operator works? What if you are trying to convert the number 7 into base 4? How many bit patterns are there for base 4: `00`, `01`, `10` and `11` which is 0, 1, 2 and 3. Let's see how masking works:

      0111 = 7
    & 0011 = 3
    __________
        11 = 3

So, you've "masked off" the first digit by using the `&` (bitwise and) operator instead of modulo. Now you can shift those bits to the right instead of using the division operator like so:

      0111 >> 2 = 01

And continue with the algorithm:

      01 = 1
    & 11 = 3
    ________
      01 = 1

So the number 7 in base 4 is: 13!

_You must use this algorithm for the specified bases!_
    
