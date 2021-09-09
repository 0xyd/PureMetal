# Lesson 7: Arrays and Pointer Arithmetic

Normally, assigning a value to a dereferenced pointer can handle most of the use case. The process of assigning is read/write instructions in assembly. For example, when we want to light up the red LED by *GPIODATA_DATA = LED_RED*, the compiler will generate the following instructions:

```assembly
0000029a:   494A                ldr        r1, [pc, #0x128]
0000029c:   2002                movs       r0, #2
0000029e:   6008                str        r0, [r1]
```

The controller first loads the address of the variable *GPIODATA_DATA* to the register 1. Then it copies value 0x02 to the register 0 and writes the value to the dereferenced address where the register 1 points to.

However, this implementation exists a problem because the read/write instruction will perform incorrectly when interrupts happen. If there is an interrupt happends between instruction ldr and movs, the str will likely load the non-updated value of the register 0 to the register 1.

To ensure the value won't be modified incorrectly, we would like to use pointer arithmetic to manipulate the data. 