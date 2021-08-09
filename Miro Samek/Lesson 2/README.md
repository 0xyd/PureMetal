# Lesson 2: Flow of Control

## Example 1

```c
int main(void)
{
    int counter = 0;
    while (counter < 3) {
        ++counter;
    }
	return 0;
}
```

```asm
          main():
00000298:   F1AD0D08            sub.w      r13, r13, #8
 8            int counter = 0;
0000029c:   2000                movs       r0, #0
0000029e:   9000                str        r0, [r13]
 9            while (counter < 3) {
000002a0:   9800                ldr        r0, [r13]
000002a2:   2803                cmp        r0, #3
000002a4:   DA05                bge        $C$L2
10                ++counter;
          $C$L1:
000002a6:   9800                ldr        r0, [r13]
000002a8:   1C40                adds       r0, r0, #1
000002aa:   9000                str        r0, [r13]
 9            while (counter < 3) {
000002ac:   9800                ldr        r0, [r13]
000002ae:   2803                cmp        r0, #3
000002b0:   DBF9                blt        $C$L1
12        	return 0;
          $C$L2:
000002b2:   2000                movs       r0, #0
13        }
```

We discover that the compiler produces two conditional checks: the one is 2a0-2a4 and the other is 2a6-2aa. The first one check if the value is greater or equal to the constant 3 and the second one is vice versa. *b* is the branch instruction and *ge* and *lt* are the condition: *ge* means *greater or equal* and *lt* means *lower than*. *cmp* will substract *r0* with value 3. If the result is lower than 0 than *N flag* is set to 1; in contrast, the *Z flag* is set to 1 when the result is 0. Note that the implementation of *a-b* is *a+(~b)* in the computer so 3-3 is 3+(\~3) and 011-100 in the binary form. Therefore, a borrow happens and the *C Flag* becomes 1. The calculation derives to 1011-100+001 = 000. 

*DA05* and *DBF9* encodes the branch conditions and the corresponding offsets. The first byte *D* represents the branch instruction. *A* and *B* are conditions. The last two bytes are offsets and there are represented in 2's complement. According to the THUMB Instruction Set, label specifies a full 9-bit two's complement address, the assembler places label with 1 right shift in the 8-bit offset so the offset value is shifted to right with 1 bit as well. To get the **real** offset, we have to shift the offset value with 1 bit left. Therefore, the offset value of opcode *DA05* is 5\*2 = 10. In addition, the branch offset takes account of the prefetch operation, in which PC is 1 word (4 bytes) ahead of the current instruction. When *DA05* is executed, PC moves 1 word ahead as default and another 10 bytes forward according to the offset value. As a result, the PC will prefetch opcode in 000002b2 which is 000002a4 + E (14 in decimal) = 000002b2. 

## Example 2

The same example but with the register optimization.



## References
1. [How to calculate 2's complement in hexidecimal](https://electronics.stackexchange.com/questions/32159/twos-complement-of-hexadecimal)
2. [THUMB Instruction Set](https://durant.io/courses/ce1921/ARM7-TDMI-ch5.pdf#page=37)
3. [Why is the Carry Flag set during a subtraction when zero is the minuend?](https://stackoverflow.com/questions/38166573/why-is-the-carry-flag-set-during-a-subtraction-when-zero-is-the-minuend)