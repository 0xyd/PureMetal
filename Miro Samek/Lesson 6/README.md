# Lesson 6: Bit wise operators in C

Although we can control the LED lights by assigning the hexadecimal values to the addresses of the registers, it takes time for us to convert bits to hexadecimal value. Therefore, embedded engineers like to use bit wise operators to handle read/write tasks on the registers instead.

## Bit wise operators

Common bit wise operators are: AND, OR, XOR, NOT, and right/left-shift. Their syntax in C are:

```c
c = a & b; // AND
c = a | b; // OR
c = a ^ b; // XOR
c = ~b;    // NOT
c = b >> 1; // right-shift 1 bit
c = b << 1; // left-shift 1 bit
``` 

Suppose there are three variables: a, b, and c:
```c
unsigned int a = 0xDEADBEEF;
unsigned int b = 0x0FF1CE10;
unsigned int c;
```

Here, we enumerate the bits operators and their corresponding instructions in the assembly.

*c = a & b;* uses instruction *ands Rd Rn* to operate bitwise AND operation. After the operation, the instruction will store the value in Rd.
```assembly
00000280:   9801                ldr        r0, [r13, #4]
00000282:   9900                ldr        r1, [r13]
00000284:   4008                ands       r0, r1
00000286:   9002                str        r0, [r13, #8]
```
*c = a | b;* uses instruction *orrs Rd Rn* to operate bitwise OR operation. Similar to ands instruction, the result will be stored in Rd.

```assembly
00000278:   9900                ldr        r1, [r13]
0000027a:   9801                ldr        r0, [r13, #4]
0000027c:   4308                orrs       r0, r1
0000027e:   9002                str        r0, [r13, #8]
```

*c = a ^ b;* uses instruction *eors* to operate XOR operation. Similar to ands instruction, the result will be stored in Rd.

```assembly
00000288:   9801                ldr        r0, [r13, #4]
0000028a:   9900                ldr        r1, [r13]
0000028c:   4048                eors       r0, r1
0000028e:   9002                str        r0, [r13, #8]
```

*c = ~b;* uses instruction *mvns Rd Rs* to run NOT operation. As usual, Rd is where the NOT result outputs.

```assembly

00000290:   9801                ldr        r0, [r13, #4]
00000292:   43C0                mvns       r0, r0
00000294:   9002                str        r0, [r13, #8]

```

For *c = a << 3;*, the microcontroller uses instruction *LSL Rd, Rs, #Offset5* to left shift the RS by *#Offset5* bits where Offset5 is 3. Then, the result will be stored into *Rd*. To shift bits to the right, it uses instruction *LSR Rd, Rs, #Offset5* instead. When the flag *S* is set, the condition flags are updated depending on the result of the operation.
```assembly
00000296:   9800                ldr        r0, [r13]
00000298:   00C0                lsls       r0, r0, #3
0000029a:   9002                str        r0, [r13, #8]
```

## Example 

Unlike the previous example, the LED lights take turns to blink. Here we want to make the task more complicated: First the red LED lights up, then the green, and the blue. Then, the red LED turns off, then the green, and the blue in the end.

Based on the information we learned from the previos lessons, the 1-3 bits of the data register control the three LEDs: Red, Green, and Blue. Instead of assiging the value, we can take advantage of bit shifting to control the LEDs. That is:

```c
#define LED_RED  (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
```

We first declare *1U* in binary, *1U << 1* shifts the 0x1 left by 1 bit to 0x10 which turns the red LED on. To turn on the blue LED, we shift the bit 1 left by 2 bits. For the green LED, we shift it by 3 bits. These marco can not only use to manipulate data register, they can use to switch on the digital signal of LEDs and change the pin states to output as well.

```c


```



## Reference
1. [Bit-wise operators in C by Miro Samek](https://www.youtube.com/watch?v=7Iru_LM3qY0&list=PLPW8O6W-1chwyTzI3BHwBLbGQoPFxPAPM&index=35)
2. [THUMB Instruction Set](https://durant.io/courses/ce1921/ARM7-TDMI-ch5.pdf)