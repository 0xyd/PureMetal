# Lesson 8: Functions in C and the call Stack

Functions are one of the most important features we can use. It can prevent us to write code that repeats itself and modularize the code for reusing. In this lesson, we are going to learn how the stack of functions work in C in the low-level implementation. Besides, we will learn how to write a proper c function that is easy to maintain and understand. 

## Refactor the code 

In the previous lessons, there are 6 conditions that control the LEDs. We access the LED by writting to the masked value in every condition. Unfortunately, the implementation is not concise because the control of LED is separated in different lines of the code. Moreover, the code will become very nasty when we want to control multiple LEDs in a condition. To make code more easily to understand, we can put all lines related to LED control into one single function and use an array with 3 elements as a flag for each LED. The first to the last element of the array is red, blue and green. Here is what the control function looks like:

```c
void controlLED(int *rgb) {

    if (rgb[0] == 1) {
        GPIODATA_PORT_F_BASE[LED_RED] = LED_RED;
    } else {
        GPIODATA_PORT_F_BASE[LED_RED] &= ~LED_RED;
    }

    if (rgb[1] == 1) {
        GPIODATA_PORT_F_BASE[LED_BLUE] = LED_BLUE;
    } else {
        GPIODATA_PORT_F_BASE[LED_BLUE] &= ~LED_BLUE;
    }

    if (rgb[2] == 1) {
        GPIODATA_PORT_F_BASE[LED_GREEN] = LED_GREEN;
    } else {
        GPIODATA_PORT_F_BASE[LED_GREEN] &= ~LED_GREEN;
    }
}
``` 

The orginal code in the loop is the following:

```c
if (counter < 1e5) {
    GPIODATA_PORT_F_BASE[LED_RED] = LED_RED;
}
if (counter >= 1e5 && counter < 2e5) {
    GPIODATA_PORT_F_BASE[LED_BLUE] = LED_BLUE;
}
if (counter >= 2e5 && counter < 3e5) {
    GPIODATA_PORT_F_BASE[LED_GREEN] = LED_GREEN;
}
if (counter >= 3e5 && counter < 4e5) {
    GPIODATA_PORT_F_BASE[LED_RED] &= ~LED_RED;
}
if (counter >= 4e5 && counter < 5e5) {
    GPIODATA_PORT_F_BASE[LED_GREEN] &= ~LED_GREEN;
}
if (counter >= 5e5 && counter < 6e5) {
    GPIODATA_PORT_F_BASE[LED_BLUE] &= ~LED_BLUE;
}
if (counter >= 6e5) {
    counter = 0;
}

```

Let's substitute the code with the new function, the code becomes:
```c
if (counter < 1e5) { // Red lights up
    rgb[0] = 1;
}
if (counter >= 1e5 && counter < 2e5) { // Blue and Red light up
    rgb[1] = 1;
}
if (counter >= 2e5 && counter < 3e5) { // All light up
    rgb[2] = 1;
}
if (counter >= 3e5 && counter < 4e5) { // Red turns off
    rgb[0] = 0;
}
if (counter >= 4e5 && counter < 5e5) { // Green turns off
    rgb[1] = 0;
}
if (counter >= 5e5 && counter < 6e5) { // Blue turns off
    rgb[2] = 0;
}
if (counter >= 6e5) {
    counter = 0;
}
controlLED(rgb);
```

If we want to control more LED simultaneously in a condition, we can simply modify other elements of the rgb to 0 or 1 just like:
```c
if (counter < 1e5) { // Light up the red and the blue
    rgb[0] = 1;
    rgb[1] = 1;
}
```

## Function Prototype

Function prototype is considered as the best practice of writing c code, it is okay to do *declare* and *define* both at once though. If a function has no prototype, the compiler will infer a prototype based on the signature of a function. The signature of a function is made of function's parameters and its name, the type of return *is not included* in the signature. For instance, there are two functions and none of them has a prototype:

```c
int add(int a, int b) { ... }
float add(int a, int b) { ... }
```  

For C compiler, this will still cause errors since both function have the same name. However, c++ accepts functions have the same name when they have different parameters. Both functions have exactly the same signature in the view of the c++ compiler. Thus, calling *add(a, b);* does make compiler confused and cause errors. With function prototype, the compiler will check the functions in compilation and this confusing declaration will be reported by the compiler.


## How does function call work in assembly

When function *controlLED* is invoked, the compiler generates the following assembly:

```assembly
46                controlLED(rgb);
          $C$L8:
00000374:   4668                mov        r0, r13
00000376:   F000F801            bl         controlLED
```

The function contains a parameter named *rgb* where we pass the 3-element array. According to *Procedure Call Standard for the Arm Architecture*, the r0-r3 registers are *Argument/Scratch registers* whose main job is to store the parameter values. Note that the 5th and the later parameters are no longer stored in the argument registers, they are stored in the stack. 

In this case, r13 register stores the memory address of the array rgb so the processor will put the stored value in r13 in register r0. 

*bl* instruction is called *long branch with link*. What it does is to jump the current procedure to the subroutine (ex: controlLED) and put the instruction next to the subroutine to the link register, r14. The address of the instruction next to the bl is 0x0000037a where the while loop starts. Interestingly, when we run the bl instruction, the link register (LR) gets the value of 0x0000037b instead of 0x0000037a. The reason is that the last bit of the LR is *the instruction set exchange bit*. If the bit is 1, the processor switches to the thumb instruction set; if the bit is 0, it switches to the ARM instruction set. Since the board is Cortex-M processor that only supports the thumb instruction, the last significant bit is always 1.   

r13 register stores the stack pointer, SP, in the arm architecture. Stack pointer always points to the top of the stack. Once the function is invoked, we observe that the value of the stack pointer is deducted by constrant value 8. As we have known from the previous lessons, the instruction *sub* means substract. *sub.w* is the variant of the substract instruction and the suffix *w* hints *wide*. In other words, it supports more immediate values. In Arm architecture, when the stack is growing, the stack pointer is deducted to point to *the higher stack*. 

After several value comparison, the processor is going to clear out the stack. Therefore, the value of the SP increases to *pop out* stacks. As the last two instructions show, SP is added by the previosly deducted value. Then, the *bx* instruction set is executed to jump to the address stored in the LR for the proceding.  

```assembly
55        void controlLED(int *rgb) {
          controlLED():
0000037c:   F1AD0D08            sub.w      r13, r13, #8
00000380:   9000                str        r0, [r13]
57            if (rgb[0] == 1) {
00000382:   9800                ldr        r0, [r13]
00000384:   6800                ldr        r0, [r0]
00000386:   2801                cmp        r0, #1
00000388:   D103                bne        $C$L9
58                GPIODATA_PORT_F_BASE[LED_RED] = LED_RED;
0000038a:   4921                ldr        r1, [pc, #0x84]
0000038c:   2002                movs       r0, #2
0000038e:   6008                str        r0, [r1]
00000390:   E004                b          $C$L10
60                GPIODATA_PORT_F_BASE[LED_RED] &= ~LED_RED;
          $C$L9:
00000392:   491F                ldr        r1, [pc, #0x7c]
00000394:   6808                ldr        r0, [r1]
00000396:   F0200002            bic        r0, r0, #2
0000039a:   6008                str        r0, [r1]
63            if (rgb[1] == 1) {
          $C$L10:
0000039c:   9800                ldr        r0, [r13]
0000039e:   6840                ldr        r0, [r0, #4]
000003a0:   2801                cmp        r0, #1
000003a2:   D103                bne        $C$L11
64                GPIODATA_PORT_F_BASE[LED_BLUE] = LED_BLUE;
000003a4:   491B                ldr        r1, [pc, #0x6c]
000003a6:   2004                movs       r0, #4
000003a8:   6008                str        r0, [r1]
000003aa:   E004                b          $C$L12
66                GPIODATA_PORT_F_BASE[LED_BLUE] &= ~LED_BLUE;
          $C$L11:
000003ac:   4919                ldr        r1, [pc, #0x64]
000003ae:   6808                ldr        r0, [r1]
000003b0:   F0200004            bic        r0, r0, #4
000003b4:   6008                str        r0, [r1]
69            if (rgb[2] == 1) {
          $C$L12:
000003b6:   9800                ldr        r0, [r13]
000003b8:   6880                ldr        r0, [r0, #8]
000003ba:   2801                cmp        r0, #1
000003bc:   D103                bne        $C$L13
70                GPIODATA_PORT_F_BASE[LED_GREEN] = LED_GREEN;
000003be:   4916                ldr        r1, [pc, #0x58]
000003c0:   2008                movs       r0, #8
000003c2:   6008                str        r0, [r1]
000003c4:   E004                b          $C$L14
72                GPIODATA_PORT_F_BASE[LED_GREEN] &= ~LED_GREEN;
          $C$L13:
000003c6:   4914                ldr        r1, [pc, #0x50]
000003c8:   6808                ldr        r0, [r1]
000003ca:   F0200008            bic        r0, r0, #8
000003ce:   6008                str        r0, [r1]
74        }
          $C$L14:
000003d0:   B002                add        r13, #8
000003d2:   4770                bx         r14
```

## Reference
1. [Functions in C and the call Stack by Miro Samek](https://www.youtube.com/watch?v=pQs8vp7JOSk&list=PLPW8O6W-1chwyTzI3BHwBLbGQoPFxPAPM&index=34)
2. [Why use function prototypes?](https://stackoverflow.com/questions/21670671/why-use-function-prototypes)
3. [Must declare function prototype in C?](https://stackoverflow.com/questions/2575153/must-declare-function-prototype-in-c)
4. [Recommended C Style and Coding Standards by Imperial London College](https://www.doc.ic.ac.uk/lab/cplus/cstyle.html)
5. [Function Overloading in C++](https://www.csee.umbc.edu/courses/undergraduate/202/spring07/Lectures/ChangSynopses/modules/m04-overload/slides.php?print)
6. [What registers to save in the arm C calling convention?](https://stackoverflow.com/questions/261419/what-registers-to-save-in-the-arm-c-calling-convention)
7. [Procedure Call Standard for the Arm Architecture](https://developer.arm.com/documentation/ihi0042/latest)